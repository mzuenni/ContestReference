#include "../util.h"
namespace dch {
	constexpr ll INF = LL::INF;
	#include <datastructures/dynamicConvexHull.cpp>
}

struct Line {
	ll m, c;
	Line(ll m_, ll c_) : m(m_), c(c_) {}
	ll operator()(ll x) {return m*x+c;}
};

void stress_test(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 1000; tries++) {
		int n = Random::integer<int>(1, 100);

		vector<Line> naive;

		dch::HullDynamic hd;
		for (int i = 0; i < n; i++) {
			ll m = Random::integer<ll>(-range, range);
			ll c = Random::integer<ll>(-range, range);
			hd.add(m, c);
			naive.emplace_back(m, c);

			for (int j = 0; j < 100; j++) {
				ll x = Random::integer<ll>(-range, range);

				ll got = hd.query(x);
				ll expected = naive[0](x);
				for (auto l : naive) expected = max(expected, l(x));

				if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
				queries++;
			}
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	dch::HullDynamic hd;

	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll m = Random::integer<ll>(-1'000'000'000, 1'000'000'000);
		ll c = Random::integer<ll>(-1'000'000'000, 1'000'000'000);
		ll x = Random::integer<ll>(-1'000'000'000, 1'000'000'000);
		
		t.start();
		hd.add(m, c);
		hash += hd.query(x);
		t.stop();
	}
	if (t.time > 200) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test(100);
	stress_test(1'000);
	stress_test(1'000'000);
	performance_test();
}
