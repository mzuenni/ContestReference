#include "../util.h"
#include <math/extendedEuclid.cpp>
#include <math/multInv.cpp>
#include <math/linearCongruence.cpp>

ll naive(ll a, ll b, ll m) {
	for (ll x = 0; x < m; x++) {
		if ((a * x) % m == b) return x;
	}
	return -1;
}

void stress_test() {
	ll work = 0;
	ll positive = 0;
	for (ll tries = 0; tries < 500'000; tries++) {
		ll m = Random::integer<ll>(0, 1'000);
		ll a = Random::integer<ll>(0, m);
		ll b = Random::integer<ll>(0, m);

		ll got = solveLinearCongruence(a, b, m);
		ll expected = naive(a, b, m);

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << endl;
		work++;
		if (got >= 0) positive++;
	}
	cerr << "stress tested: " << work << " (" << positive << ")" << endl;
}

constexpr int N = 500'000;
void performance_test() {
	timer t;
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll m = Random::integer<ll>(0, 1'0000'000'000);
		ll a = Random::integer<ll>(0, m);
		ll b = Random::integer<ll>(0, m);

		t.start();
		hash += solveLinearCongruence(a, b, m);
		t.stop();
	}
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}


int main() {
	stress_test();
	performance_test();
}

