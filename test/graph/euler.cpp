#include "../util.h"
struct Euler {
	Euler(int n) : idx(n), validIdx(n) {}
#include <graph/euler.cpp>
};

Euler eulerGraph(int n, int m) {
	Euler res(n);

	Graph<NoData> g(n);
	g.tree();
	g.forEdges([&](int a, int b) {
		res.addEdge(a, b);
	});

	for (int i = n-1; i < m; i++) {
		int a = Random::integer<int>(0, n);
		int b = Random::integer<int>(0, n);
		res.addEdge(a, b);
	}
	int last = -1;
	for (int i = 0; i < n; i++) {
		if (sz(res.idx[i]) % 2 != 0) {
			if (last >= 0) {
				res.addEdge(last, i);
				last = -1;
			} else {
				last = i;
			}
		}
	}
	if (last >= 0) cerr << "FAIL" << FAIL;

	return res;
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 200'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(n-1, 200);

		auto g = eulerGraph(n, m);
		
		vector<vector<int>> expected(n);
		for (int i = 0; i < n; i++) {
			for (int j : g.idx[i]) {
				expected[i].push_back(g.to[j]);
			}
			sort(all(expected[i]));
		}

		g.euler(0);
		vector<vector<int>> got(n);
		if (g.cycle.front() != g.cycle.back()) cerr << "error: not cyclic" << FAIL;
		for (int i = 1; i < sz(g.cycle); i++) {
			int a = g.cycle[i-1];
			int b = g.cycle[i];
			got[a].push_back(b);
			got[b].push_back(a);
		}
		for (auto& v : got) sort(all(v));

		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 100'000;
constexpr int M = 1'000'000;
void performance_test() {
	timer t;
	auto g = eulerGraph(N, M);
	t.start();
	g.euler(0);
	t.stop();
	hash_t hash = 0;
	for (int x : g.cycle) hash += x;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
