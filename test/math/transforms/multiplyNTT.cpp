#include "../../util.h"
#include <math/modPowIterativ.cpp>
#include <math/transforms/ntt.cpp>
#include <math/transforms/multiplyNTT.cpp>

vector<ll> naive(const vector<ll>& a, const vector<ll>& b) {
	vector<ll> res;
	for (ll i = 1;; i *= 2) {
		if (sz(a) + sz(b) <= i) {
			res.resize(i, 0);
			break;
		}
	}
	for (int i = 0; i < sz(a); i++) {
		for (int j = 0; j < sz(b); j++) {
			res[i+j] += a[i] * b[j];
			res[i+j] %= mod;
		}
	}
	return res;
}

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 100);
		int m = Random::integer<int>(1, 100);
		auto a = Random::integers<ll>(n, 0, mod);
		auto b = Random::integers<ll>(m, 0, mod);
		auto expected = naive(a, b);
		auto got = mul(a, b);
		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 1ll << 20;
void performance_test() {
	timer t;
	vector<ll> a = Random::integers<ll>(N, 0, mod);
	vector<ll> b = Random::integers<ll>(N, 0, mod);
	t.start();
	auto got = mul(a, b);
	t.stop();
	hash_t hash = 0;
	for (ll i = 0; i < N; i++) hash += i * got[i];
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

