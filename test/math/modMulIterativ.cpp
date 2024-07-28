#include "../util.h"
#include <math/modMulIterativ.cpp>

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int a = Random::integer<int>(1, 100);
		int n = Random::integer<int>(2, 100);
		ll expected = 0;
		ll k = 0;
		do {
			auto got = mulMod(a, k, n);
			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
			k++;
			expected = (expected + a) % n;
		} while (k < 100);
		queries += n;
	}
	cerr << "tested queries: " << queries << endl;
}

void stress_test_large() {
	ll queries = 0;
	for (ll i = 0; i < 1000'000; i++) {
		ll a = Random::integer<ll>(0, 1'000'000'000'000'000'000);
		ll b = Random::integer<ll>(0, 1'000'000'000'000'000'000);
		ll n = Random::integer<ll>(2, 1'000'000'000'000'000'000);
		ll expected = (lll)a * b % n;
		auto got = mulMod(a, b, n);
		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 500'000;
void performance_test() {
	timer t;
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll a = Random::integer<ll>(0, 1'000'000'000'000'000'000);
		ll b = Random::integer<ll>(0, 1'000'000'000'000'000'000);
		ll n = Random::integer<ll>(2, 1'000'000'000'000'000'000);
		t.start();
		hash += mulMod(a, b, n);
		t.stop();
	}
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	stress_test_large();
	performance_test();
}

