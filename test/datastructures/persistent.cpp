#include "../util.h"
#pragma GCC diagnostic ignored "-Wshadow"
#include <datastructures/persistent.cpp>

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 30);

		int timeRef = Random::integer<int>(1, 30);
		persistent<double> got(timeRef);
		map<int, double> expected;

		for (int i = 0; i < n; i++) {
			timeRef += Random::integer<int>(1, 30);
			double x = Random::real<double>(-1'000, 1'000);
			auto t = got.set(x);

			if (!expected.empty() && t <= expected.rbegin()->first) cerr << "error: time travel" << FAIL;
			expected[t] = x;
		}

		double tmp = 0;
		for (int i = expected.begin()->first; i < expected.rbegin()->first + 10; i++) {
			if (expected.find(i) != expected.end()) tmp = expected[i];
			if (got.get(i) != tmp) cerr << "got: " << got.get(i) << ", " << "expected: " << tmp << FAIL;
		}
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

int main() {
	stress_test();
}
