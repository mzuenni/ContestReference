#include "../util.h"
namespace tutte {
void gauss(int n, ll mod);
#include <graph/matching.cpp>
#include <math/shortModInv.cpp>
#include <math/lgsFp.cpp>
}
#include <graph/blossom.cpp>

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 5'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(0, max<int>(1, n*(n-1) / 2 + 1));

		GM blossom(n);
		srand(Random::rng());
		tutte::adj.assign(n, {});

		Graph<NoData> g(n);
		g.erdosRenyi(m);
		g.forEdges([&](int a, int b){
			tutte::adj[a].push_back(b);
			tutte::adj[b].push_back(a);

			blossom.adj[a].push_back(b);
			blossom.adj[b].push_back(a);
		});

		ll got = tutte::max_matching();
		ll expected = blossom.match();

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 125;
constexpr int M = 5'000;
void performance_test() {
	timer t;
	Graph<NoData> g(N);
	g.erdosRenyi(M);
	srand(Random::rng());
	tutte::adj.assign(N, {});
	g.forEdges([&](int a, int b){
			tutte::adj[a].push_back(b);
			tutte::adj[b].push_back(a);
	});

	t.start();
	hash_t hash = tutte::max_matching();
	t.stop();
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
