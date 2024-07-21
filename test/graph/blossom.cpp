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

		ll got = blossom.match();
		ll expected = tutte::max_matching();

		vector<bool> seen(n);
		ll got2 = 0;
		for (int i = 0; i < n; i++) {
			int j = blossom.pairs[i];
			if (j >= n) continue;
			if (blossom.pairs[j] != i) cerr << "error: inconsitent" << FAIL;
			if (j == i) cerr << "error: invalid" << FAIL;
			if (j < i) continue;
			if (seen[i] || seen[j]) cerr << "error: invalid" << FAIL;
			seen[i] = seen[j] = true;
			got2++;
		}

		if (got != got2) cerr << "got: " << got << ", got2: " << got2 << FAIL;
		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

//this is an easy graph...
constexpr int N = 100'000;
constexpr int M = 500'000;
void performance_test() {
	timer t;
	Graph<NoData> g(N);
	g.erdosRenyi(M);
	GM blossom(N);
	g.forEdges([&](int a, int b){
		blossom.adj[a].push_back(b);
		blossom.adj[b].push_back(a);
	});

	t.start();
	hash_t hash = blossom.match();
	t.stop();
	if (t.time > 200) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
