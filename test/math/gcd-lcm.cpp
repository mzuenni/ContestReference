#include "../util.h"
#include <math/gcd-lcm.cpp>

void stress_test() {
	if (::gcd(0, 0) != 0) cerr << "error: gcd(0, 0)" << FAIL;
	if (::lcm(0, 0) != 0) cerr << "error: lcm(0, 0)" << FAIL;
	ll queries = 0;
	timer t;
	for (int i = 0; i < 1'000'000; i++) {
		ll a = Random::integer<ll>(0, 1'000'000'000);
		ll b = 0;
		{
			ll got = ::gcd(a, b);
			ll expected = std::gcd(a, b);
			if (got != expected) cerr << "gcd(" << a << ", " << b << "), got: " << got << ", expected: " << expected << FAIL;
		}
		{
			ll got = ::lcm(a, b);
			ll expected = std::lcm(a, b);
			if (got != expected) cerr << "lcm(" << a << ", " << b << "), got: " << got << ", expected: " << expected << FAIL;
		}
		b = Random::integer<ll>(0, 1'000'000'000);
		{
			t.start();
			ll got = ::gcd(a, b);
			t.stop();
			ll expected = std::gcd(a, b);
			if (got != expected) cerr << "gcd(" << a << ", " << b << "), got: " << got << ", expected: " << expected << FAIL;
		}
		{
			t.start();
			ll got = ::lcm(a, b);
			t.stop();
			ll expected = std::lcm(a, b);
			if (got != expected) cerr << "lcm(" << a << ", " << b << "), got: " << got << ", expected: " << expected << FAIL;
		}
		queries++;
	}
	cerr << "tested random queries: " << queries << endl;
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms" << endl;
}

int main() {
	stress_test();
}
