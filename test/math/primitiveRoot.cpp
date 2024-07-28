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

bool naiveIsPrimitive(ll g, ll n) {
	if (gcd(g, n) != 1) return false;
	vector<bool> seen(n);
	ll c = g;
	for (ll i = 0; i < n; i++) {
		seen[c] = true;
		c = (c * g) % n;
	}
	ll res = 0;
	for (bool x : seen) if (x) res++;
	return res == phi(n);
}

void stress_test() {
	int queries = 0;
	for (int tries = 0; tries < 20'000; tries++) {
		ll a = Random::integer<ll>(1, 3);
		ll p = Random::prime<ll>(0, 1000);
		ll k = p == 2 ? 1 : Random::integer<ll>(1, log(100'000) / log(p) + 1);

		ll x = a;
		for (int i = 0; i < k; i++) x *= p;

		ll got = findPrimitive(x);

		if (got < 0 || got >= x) cerr << "error: out of range" << FAIL;
		if (!naiveIsPrimitive(got, x)) cerr << "error: wrong" << got << " " << x << FAIL;
		queries++;
	}
	cerr << "tested random queries: " << queries << endl;
}

void stress_test2() {
	int queries = 0;
	for (int x = 2; x < 5'000; x++) {
		map<ll, int> facts;
		factor(x, facts);
		if (x % 2 == 0) facts.erase(facts.find(2));
		bool expected = sz(facts) == 1;
		if (x % 4 == 0) expected = false;
		if (x == 2 || x == 4) expected = true;

		bool got = findPrimitive(x) >= 0;

		if (got != expected) cerr << "error" << FAIL;
		queries++;
	}
	cerr << "tested random queries: " << queries << endl;
}

int main() {
	stress_test();
	stress_test2();
}

