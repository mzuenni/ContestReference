#include "../util.h"
#include <math/primeSieve.cpp>

bool naive(ll x) {
	for (ll i = 2; i*i <= x; i++) {
		if (x % i == 0) return false;
	}
	return x > 1;
}

void stress_test() {
	int queries = 0;
	vector<ll> found;
	for (int i = -5; i < 1'000'000; i++) {
		auto got = isPrime(i);
		auto expected = naive(i);
		if (got != expected) cerr << "error: " << i << FAIL;
		if (got) found.push_back(i);
		queries++;
	}
	primes.resize(sz(found));
	if (primes != found) cerr << "error: primes" << FAIL;
	for (int i = 0; i < 1'000'000; i++) {
		ll x = Random::integer<ll>(2, N);
		auto got = isPrime(x);
		auto expected = naive(x);
		if (got != expected) cerr << "error: " << x << FAIL;
		queries++;
	}
	cerr << "tested queries: " << queries << endl;
}

void performance_test() {
	timer t;
	t.start();
	primeSieve();
	hash_t hash = sz(primes);
	t.stop();
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	performance_test();
	stress_test();
}

