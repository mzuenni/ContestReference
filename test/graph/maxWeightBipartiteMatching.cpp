#include "../util.h"
#pragma GCC diagnostic ignored "-Wshadow"
namespace matching {
	constexpr int N_LEFT = 1000;
	constexpr int N_RIGHT = 1000;
	constexpr double INF = LD::INF;
	#include <graph/maxWeightBipartiteMatching.cpp>
}
namespace mcmf {
	#include <graph/minCostMaxFlow.cpp>
}


void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 20'000; tries++) {
		auto [l, r] = Random::pair<int>(1, 30);
		mcmf::MinCostFlow mcmf(l+r+2, 0, 1);

		for (int i = 0; i < l; i++) mcmf.addEdge(0, 2 + i, 1, 0);
		for (int i = 0; i < r; i++) mcmf.addEdge(2 + l + i, 1, 1, 0);
		for (int i = 0; i < l; i++) {
			for (int j = 0; j < r; j++) {
				matching::costs[i][j] = Random::integer<int>(-100, 100);
				mcmf.addEdge(2 + i, 2 + l + j, 1, -matching::costs[i][j]);
			}
		}

		double got = matching::match(l, r);
		mcmf.mincostflow();
		ll expected = -mcmf.mincost;

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += l + r;
	}
	cerr << "tested random queries: " << queries << endl;
}

void performance_test() {
	using namespace matching;
	timer t;

	for (int i = 0; i < N_LEFT; i++) {
		for (int j = 0; j < N_RIGHT; j++) {
			costs[i][j] = Random::integer<int>(-100, 100);
		}
	}

	t.start();
	hash_t hash = match(N_LEFT, N_RIGHT);
	t.stop();
	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
