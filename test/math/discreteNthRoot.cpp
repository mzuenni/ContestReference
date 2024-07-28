#include "../util.h"
#define ll lll
#include <math/modPowIterativ.cpp>
#undef ll
#include <math/millerRabin.cpp>
#include <math/rho.cpp>

ll phi(ll pk, ll p, ll /*k*/) {return pk - pk / p;}
ll phi(ll n) { // O(sqrt(n))
	ll res = 1;
	for (ll p = 2; p * p <= n; p++) {
		if (n % p == 0) {
			ll pk = 1;
			ll k = 0;
			do {
				n /= p;
				pk *= p;
				k++;
			} while (n % p == 0);
			res *= phi(pk, p, k);
	}}
	if (n > 1) res *= phi(n, n, 1);
	return res;
}

#include <math/primitiveRoot.cpp>
#include <math/discreteLogarithm.cpp>
#include <math/discreteNthRoot.cpp>

//x^a=b mod m
ll naiveRoot(ll a, ll b, ll m) {
	for (ll i = 0; i < m; i++) {
		if (powMod(i, a, m) == b) return i;
	}
	return -1;
}

void stress_test() {
	int queries = 0;
	int found = 0;
	for (int tries = 0; tries < 50'000; tries++) {
		ll p = Random::prime<ll>(0, 1000);
		ll a = Random::integer<ll>(1, p);
		ll b = Random::integer<ll>(1, p);

		ll got = root(a, b, p);
		ll expected = naiveRoot(a, b, p);

		if (got < -1 || got >= p) cerr << "error: out of range" << FAIL;
		if (got >= 0 && powMod(got, a, p) != b) cerr << "error: wrong" << FAIL;
		if ((got >= 0) != (expected >= 0)) cerr << "error" << FAIL;
		queries++;
		if (expected >= 0) found++;
	}
	cerr << "tested random queries: " << queries << " (" << found << ")" << endl;
}

constexpr int N = 50;
constexpr ll mod = 1'394'633'899;
void performance_test() {
	timer t;
	hash_t hash = 0;
	for (int i = 0; i < N; i++) {
		ll a = Random::integer<ll>(1, mod);
		ll b = Random::integer<ll>(1, mod);
		t.start();
		hash += root(a, b, mod);
		t.stop();
	}
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

