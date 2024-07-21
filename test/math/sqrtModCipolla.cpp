#include "../util.h"
#include <math/modPowIterativ.cpp>
#include <math/legendre.cpp>
mt19937 rng(123456789);
#include <math/sqrtModCipolla.cpp>

void stress_test(ll range) {
	ll work = 0;
	for (ll i = 0; i < 10'000; i++) {
		ll p = Random::prime<ll>(range);
		for (ll j = 0; j < 100; j++) {
			ll x = Random::integer<ll>(0, p);
			if (legendre(x, p) < 0) continue;

			ll got = sqrtMod(x, p);
			if (got < 0 || got >= p) cerr << "error: out of range" << FAIL;
			if ((got * got) % p != x) cerr << "error: not root" << FAIL;
			work++;
		}
	}
	cerr << "stress tested: " << work << endl;
}

constexpr int N = 200'000;
constexpr ll mod = 1'394'633'899;
void performance_test() {
	timer t;
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll x;
		do {
			x = Random::integer<ll>(0, mod);
		} while (legendre(x, mod) >= 0);
		t.start();
		hash += sqrtMod(x, mod);
		t.stop();
	}
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}


int main() {
	stress_test(1'000);
	stress_test(1'000'000'000);
	performance_test();
}

