#include "../util.h"
namespace kuhn {
#include <graph/maxCarBiMatch.cpp>
}
namespace hk {
#include <graph/hopcroftKarp.cpp>
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 50'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(0, max<int>(1, n*(n-1) / 2 + 1));

		kuhn::adj.assign(2*n, {});
		hk::adj.assign(2*n, {});

		Graph<NoData> g(n);
		g.erdosRenyi(m);
		g.forEdges([&](int a, int b){
			kuhn::adj[a].push_back(n+b);
			kuhn::adj[b+n].push_back(a);

			hk::adj[a].push_back(n+b);
			hk::adj[b+n].push_back(a);
		});

		ll got = kuhn::kuhn(n);
		ll expected = hk::hopcroft_karp(n);

		vector<bool> seen(2*n);
		ll got2 = 0;
		for (int i = 0; i < n; i++) {
			int j = kuhn::pairs[i];
			if (j < 0) continue;
			if (kuhn::pairs[j] != i) cerr << "error: inconsitent" << FAIL;
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
constexpr int N = 10'000;
constexpr int M = 100'000;
void performance_test() {
	timer t;
	Graph<NoData> g(N);
	g.erdosRenyi(M);
	kuhn::adj.assign(2*N, {});
	g.forEdges([&](int a, int b){
		kuhn::adj[a].push_back(N+b);
		kuhn::adj[b+N].push_back(a);
	});

	t.start();
	hash_t hash = kuhn::kuhn(N);
	t.stop();
	if (t.time > 200) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
