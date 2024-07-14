#include "../../util.h"
#include <math/modPowIterativ.cpp>
#include <math/transforms/ntt.cpp>

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int n = 1ll << Random::integer<int>(0, 10);
		auto expected = Random::integers<ll>(n, 0, mod);
		auto got = expected;
		ntt(got, false);
		ntt(got, true);
		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 1ll << 22;
void performance_test() {
	timer t;
	vector<ll> a = Random::integers<ll>(N, 0, mod);
	vector<ll> b = Random::integers<ll>(N, 0, mod);
	t.start();
	ntt(a, true);
	ntt(b, false);
	t.stop();
	hash_t hash = 0;
	for (ll i = 0; i < N; i++) hash += i * a[i];
	for (ll i = 0; i < N; i++) hash += i * b[i];
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

