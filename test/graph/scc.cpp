#include "../util.h"
#include <graph/scc.cpp>
#include <datastructures/unionFind.cpp>

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(0, max<int>(1, min<int>(100, n*(n-1) / 2 + 1)));
		Graph<NoData, true> g(n);
		g.erdosRenyi(m);

		adj.assign(n, {});
		g.forEdges([](int a, int b){
			adj[a].push_back(b);
		});
		scc();

		init(n);
		vector<ll> seen(n);
		int tmpCounter = 0;
		auto reach = [&](int a, int b) {
			tmpCounter++;
			seen[a] = tmpCounter;
			vector<int> todo = {a};
			while (seen[b] != tmpCounter && !todo.empty()) {
				a = todo.back();
				todo.pop_back();
				g.forOut(a, [&](int /**/, int x){
					if (seen[x] != tmpCounter) {
						seen[x] = tmpCounter;
						todo.push_back(x);
					}
				});
			}
			return seen[b] == tmpCounter;
		};
		for (int a = 0; a < n; a++) {
			for (int b = 0; b < a; b++) {
				if (findSet(a) == findSet(b)) continue;
				if (reach(a, b) && reach(b, a)) unionSets(a, b);
			}
		}

		for (int a = 0; a < n; a++) {
			for (int b = 0; b <= a; b++) {
				bool got = idx[a] == idx[b];
				bool expected = findSet(a) == findSet(b);
				if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
			}
		}
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 500'000;
constexpr int M = 2'000'000;
void performance_test() {
	timer t;
	Graph<NoData, true> g(N);
	g.erdosRenyi(M);
	adj.assign(N, {});
	g.forEdges([](int a, int b){
		adj[a].push_back(b);
	});

	t.start();
	scc();	
	t.stop();
	hash_t hash = 0;
	for (int x : idx) hash += x;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
