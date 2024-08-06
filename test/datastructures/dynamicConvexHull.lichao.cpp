#include "../util.h"
constexpr ll INF = LL::INF;
#include <datastructures/dynamicConvexHull.cpp>
#include <datastructures/lichao.cpp>

void stress_test(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 1000; tries++) {
		int n = Random::integer<int>(1, 100);
		xs = Random::distinct(n, -range, range);
		sort(all(xs));

		HullDynamic hd;
		Lichao lichao;
		for (int i = 0; i < 1000; i++) {
			ll m = Random::integer<ll>(-range, range);
			ll c = Random::integer<ll>(-range, range);
			hd.add(m, c);
			lichao.insert({-m, -c});

			for (ll x : xs) {
				ll gotA = hd.query(x);
				ll gotB = -lichao.query(x);

				if (gotA != gotB) cerr << "gotA: " << gotA << ", gotB: " << gotB << FAIL;
				queries++;
			}
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

int main() {
	stress_test(100);
	stress_test(1'000);
	stress_test(1'000'000);
}
