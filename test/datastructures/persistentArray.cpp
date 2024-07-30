#include "../util.h"
#pragma GCC diagnostic ignored "-Wshadow"
#include <datastructures/persistent.cpp>
#include <datastructures/persistentArray.cpp>

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 2'000; tries++) {
		int n = Random::integer<int>(1, 30)*1000;
		int m = Random::integer<int>(1, 30);

		persistentArray<double> got(m);
		vector<double> cur(m);
		vector<pair<int, vector<double>>> expected;
		for (int i = 0; i < n; i++) {
			int op = Random::integer<int>(0, 20);
			if (op <= 10) {
				int j = Random::integer<int>(0, m);
				double x = Random::real<double>(-1'000, 1'000);

				auto t = got.set(j, x);
				if (!expected.empty() && t <= expected.rbegin()->first) cerr << "error: time travel" << FAIL;

				cur[j] = x;
				expected.emplace_back(t, cur);
			} else if (op <= 16) {
				if (sz(expected) < 1) continue;
				int j = Random::integer<int>(0, sz(expected));
				for (int k = 0; k < m; k++) {
					if (got.get(k, expected[j].first) != expected[j].second[k]) cerr << "got: " << got.get(k, expected[j].first) << ", expected: " << expected[j].second[k] << FAIL;
				}
			} else {
				if (sz(expected) < 1) continue;
				int j = Random::integer<int>(0, sz(expected));
				got.reset(expected[j].first);
				expected.resize(j + 1);
				cur = expected.back().second;
			}
			
		}
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

int main() {
	stress_test();
}
