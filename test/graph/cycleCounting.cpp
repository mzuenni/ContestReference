#include "../util.h"
#include <datastructures/unionFind.cpp>
#include <graph/cycleCounting.cpp>

int naive(const vector<pair<int, int>>& edges, int n) {
	int res = 0;
	for (int i = 1; i < (1ll << sz(edges)); i++) {
		vector<int> deg(n);
		init(n);
		int cycles = 0;
		for (int j = 0; j < sz(edges); j++) {
			if (((i >> j) & 1) != 0) {
				auto [a, b] = edges[j];
				deg[a]++;
				deg[b]++;
				if (findSet(a) != findSet(b)) {
					unionSets(a, b);
				} else {
					cycles++;
				}
			}
		}
		bool ok = cycles == 1;
		for (auto d : deg) ok &= d == 0 || d == 2;
		if (ok) res++;
	}
	return res;
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 50'000; tries++) {
		int n = Random::integer<int>(1, 8);
		int m = Random::integer<int>(0, min<int>(15, n*(n-1) / 2 + 1));

		Graph<NoData, 0, 1, 1> g(n);
		g.erdosRenyi(m);
		vector<pair<int, int>> edges;
		cycles cyc(n);
		g.forEdges([&](int a, int b){
			edges.emplace_back(a, b);
			cyc.addEdge(a, b);
		});

		int expected = naive(edges, n);
		int got = cyc.count();

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 100;
constexpr int M = 20;
void performance_test() {
	timer t;

	Graph<NoData> g(N);
	g.tree();
	g.erdosRenyi(M);
	cycles cyc(N);
	g.forEdges([&](int a, int b){
		cyc.addEdge(a, b);
	});

	t.start();
	hash_t hash = cyc.count();
	cerr << sz(cyc.base) << endl;
	t.stop();

	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
