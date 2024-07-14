#include "../util.h"
#include <math/modPowIterativ.cpp>

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int a = Random::integer<int>(1, 100);
		int n = Random::integer<int>(2, 100);
		ll expected = 1;
		ll k = 0;
		do {
			auto got = powMod(a, k, n);
			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
			k++;
			expected = (expected * a) % n;
		} while (k < 100);
		queries += n;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll a = Random::integer<ll>(0, 1'000'000'000);
		ll b = Random::integer<ll>(0, 1'000'000'000);
		ll n = Random::integer<ll>(2, 1'000'000'000);
		t.start();
		hash += powMod(a, b, n);
		t.stop();
	}
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

