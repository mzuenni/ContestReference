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

		mcmf.mincostflow();
		ll got = -mcmf.mincost;
		double expected = matching::match(l, r);

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += l + r;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 1'000;
constexpr int M = 10'000;
void performance_test() {
	using namespace mcmf;
	timer t;

	Graph<NoData> g(N);
	g.erdosRenyi(M);
	MinCostFlow mcmf(N, 0, 1);
	vector<ll> potential = Random::integers<ll>(N, 0, 1'000'000ll);
	g.forEdges([&](int a, int b){
		ll c = Random::integer<ll>(1, 1000'000);
		ll cost = Random::integer<ll>(0, 1000'000);
		mcmf.addEdge(a, b, c, potential[b] + cost - potential[a]);
		mcmf.addEdge(b, a, c, potential[a] + cost - potential[b]);
	});

	t.start();
	mcmf.mincostflow();
	t.stop();

	hash_t hash = mcmf.mincost;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
