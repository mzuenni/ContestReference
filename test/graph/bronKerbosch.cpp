#include "../util.h"
#include <graph/bronKerbosch.cpp>

vector<bits> naiveCliques;

void naive(bits mask = {}, int l = 0) {
	bool maximal = true;
	for (ll i = 0; i < l; i++) {
		if (mask[i]) continue;
		if ((adj[i] & mask) == mask) maximal = false;
	}
	for (; l < sz(adj); l++) {
		if ((adj[l] & mask) == mask) {
			maximal = false;
			mask[l] = 1;
			naive(mask, l + 1);
			mask[l] = 0;
		}
	}
	if (maximal and mask.any()) naiveCliques.push_back(mask);
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 200'000; tries++) {
		int n = Random::integer<int>(2, 15);
		int m = Random::integer<int>(0, max<int>(n, min<int>(500, n*(n-1) / 2 + 1)));

		Graph<NoData> g(n);
		g.erdosRenyi(m);
		adj.assign(n, {});
		g.forEdges([&](int a, int b){
			addEdge(a, b);
		});

		bronKerbosch();
		naiveCliques.clear();
		naive();

		sort(all(cliques), [](bits a, bits b){return a.to_ullong()  < b.to_ullong();});
		sort(all(naiveCliques), [](bits a, bits b){return a.to_ullong()  < b.to_ullong();});

		if (cliques != naiveCliques) cerr << "got: " << sz(cliques) << ", expected: " << sz(naiveCliques) << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 55;
constexpr int M = N*(N-1) / 2 - 2*N;
void performance_test() {
	timer t;

	Graph<NoData> g(N);
	g.erdosRenyi(M);
	adj.assign(N, {});
	g.forEdges([&](int a, int b){
		addEdge(a, b);
	});

	t.start();
	bronKerbosch();
	t.stop();

	hash_t hash = sz(cliques);
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
