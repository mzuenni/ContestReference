#include "../util.h"
#include <math/shortModInv.cpp>

void stress_test() {
	ll queries = 0;
	for (int i = 0; i < 10'000'000; i++) {
		ll n = Random::integer<ll>(2, 1'000'000'000);
		ll x = 0;
		do {
			x = Random::integer<ll>(0, n);
		} while (gcd(x, n) != 1);
		ll y = multInv(x, n);
		ll got = (x*y) % n;
		if (got != 1) cerr << "got: " << got << ", expected: 1" << FAIL;
		queries++;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll a = Random::integer<ll>(0, 1'000'000'000);
		ll b = Random::integer<ll>(2, 1'000'000'000);
		t.start();
		hash += multInv(a, b);
		t.stop();
	}
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

