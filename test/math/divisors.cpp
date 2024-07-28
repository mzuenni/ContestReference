#include "../util.h"
#define ll lll
#include <math/modPowIterativ.cpp>
#undef ll
#include <math/millerRabin.cpp>

bool isSquare(ll x) {
	ll r = sqrtl(x);
	while (r*r > x) r--;
	while ((r+1)*(r+1) <= x) r++;
	return r*r==x;
}

#include <math/divisors.cpp>

ll naive(ll x) {
	ll res = 0;
	for (ll i = 1; i*i <= x; i++) {
		if (x % i == 0) {
			res++;
			if (i*i != x) res++;
		}
	}
	return res;
}

void stress_test() {
	ll work = 0;
	for (ll i = 0; i < 1'000; i++) {
		ll x = Random::integer<ll>(1, 1'000'000'000'000);
		auto got = countDivisors(x);
		auto expected = naive(x);
		if (got != expected) cerr << "error: " << x << FAIL;
		work += sqrt(x);
	}
	for (ll i = 0; i < 100'000; i++) {
		ll x = Random::integer<ll>(1, 1'000'000);
		auto got = countDivisors(x);
		auto expected = naive(x);
		if (got != expected) cerr << "error: " << x << FAIL;
		work += sqrt(x);
	}
	cerr << "stress tested: " << work << endl;
}

constexpr int N = 200;
void performance_test() {
	timer t;
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll x = Random::integer<ll>(1e18 / 2, 1e18);
		t.start();
		hash += countDivisors(x);
		t.stop();
	}
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}


int main() {
	stress_test();
	performance_test();
}

