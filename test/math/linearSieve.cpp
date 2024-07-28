#include "../util.h"
namespace expected {
#include <math/primeSieve.cpp>
}
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <math/linearSieve.cpp>

void stress_test() {
	expected::primeSieve();
	expected::primes.resize(primes.size());
	if (expected::primes != primes) cerr << "error: primes" << FAIL;
	int queries = 0;
	for (int i = 1; i < 1'000'000; i++) {
		auto got = sieved[i];
		auto expected = naive(i);
		if (got != expected) cerr << i << ", got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	for (int i = 0; i < 1'000'000; i++) {
		ll x = Random::integer<ll>(2, N);
		auto got = sieved[x];
		auto expected = naive(x);
		if (got != expected) cerr << x << ", got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested queries: " << queries << endl;
}

void test_tiny() {
	if (mu( 3, 3, 1) != -1) cerr << "error: 1" << FAIL;
	if (mu( 9, 3, 2) !=  0) cerr << "error: 2" << FAIL;
	if (mu(27, 3, 3) !=  0) cerr << "error: 3" << FAIL;

	if (phi( 3, 3, 1) !=  2) cerr << "error: 4" << FAIL;
	if (phi( 9, 3, 2) !=  6) cerr << "error: 5" << FAIL;
	if (phi(27, 3, 3) != 18) cerr << "error: 6" << FAIL;

	if (div( 3, 3, 1) !=  2) cerr << "error: 7" << FAIL;
	if (div( 9, 3, 2) !=  3) cerr << "error: 8" << FAIL;
	if (div(27, 3, 3) !=  4) cerr << "error: 9" << FAIL;

	if (divSum( 3, 3, 1) !=  4) cerr << "error: 10" << FAIL;
	if (divSum( 9, 3, 2) != 13) cerr << "error: 11" << FAIL;
	if (divSum(27, 3, 3) != 40) cerr << "error: 12" << FAIL;

	if (square( 3, 3, 1) !=  1) cerr << "error: 13" << FAIL;
	if (square( 9, 3, 2) !=  9) cerr << "error: 14" << FAIL;
	if (square(27, 3, 3) !=  9) cerr << "error: 15" << FAIL;

	if (squareFree( 3, 3, 1) !=  3) cerr << "error: 13" << FAIL;
	if (squareFree( 9, 3, 2) !=  3) cerr << "error: 14" << FAIL;
	if (squareFree(27, 3, 3) !=  3) cerr << "error: 15" << FAIL;
	cerr << "tested tiny" << endl;
}

void performance_test() {
	timer t;
	t.start();
	sieve();
	hash_t hash = sz(primes);
	t.stop();
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	performance_test();
	stress_test();
	test_tiny();
}

