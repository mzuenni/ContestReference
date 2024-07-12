#include "../util.h"
#include <math/extendedEuclid.cpp>

void stress_test() {
	if (extendedEuclid(0, 0)[0] != 0) cerr << "error: extendedEuclid(0, 0)" << FAIL;
	ll queries = 0;
	timer t;
	for (int i = 0; i < 1'000'000; i++) {
		ll a = Random::integer<ll>(0, 1'000'000'000);
		ll b = 0;
		{
			t.start();
			auto [got, x, y] = extendedEuclid(a, b);
			t.stop();
			ll expected = std::gcd(a, b);
			if (got != expected) cerr << "gcd(" << a << ", " << b << "), got: " << got << ", expected: " << expected << FAIL;
			if (abs(x) >= max<ll>(2, abs(b))) cerr << "invalid x" << FAIL;
			if (abs(y) >= max<ll>(2, abs(a))) cerr << "invalid y" << FAIL;
			if (a*x + b*y != expected) cerr << "invalid x or y" << FAIL;
		}
		b = Random::integer<ll>(0, 1'000'000'000);
		{
			t.start();
			auto [got, x, y] = extendedEuclid(a, b);
			t.stop();
			ll expected = std::gcd(a, b);
			if (got != expected) cerr << "gcd(" << a << ", " << b << "), got: " << got << ", expected: " << expected << FAIL;
			if (abs(x) >= max<ll>(2, abs(b))) cerr << "invalid x" << FAIL;
			if (abs(y) >= max<ll>(2, abs(a))) cerr << "invalid y" << FAIL;
			if (a*x + b*y != expected) cerr << "invalid x or y" << FAIL;
		}
		queries++;
	}
	cerr << "tested random queries: " << queries << endl;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms" << endl;
}

int main() {
	stress_test();
}
