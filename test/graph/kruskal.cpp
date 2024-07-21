#include "../util.h"
#include <datastructures/unionFind.cpp>

struct edge {
	int from, to;
	ll cost;
	bool operator<(const edge& o) const {
		return cost > o.cost;
	}
};
ll kruskal(vector<edge>& edges, int n) {
	init(n);
	#define Edge edge
	#include <graph/kruskal.cpp>
	#undef Edge
	return cost;
}

ll prim(vector<edge>& edges, int n) {
	vector<vector<pair<ll, int>>> adj(n);
	for (auto [a, b, d] : edges) {
		adj[a].emplace_back(d, b);
		adj[b].emplace_back(d, a);
	}
	priority_queue<pair<ll, int>> todo;
	vector<bool> seen(n);
	ll res = 0;
	for (ll i = 0; i < n; i++) {
		if (seen[i]) continue;
		todo.push({0, i});
		while (!todo.empty()) {
			auto [d, c] = todo.top();
			todo.pop();
			if (seen[c]) continue;
			seen[c] = true;
			res += d;
			for (auto e : adj[c]) {
				todo.push(e);
			}
		}
	}
	return res;
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(2, 30);
		int m = Random::integer<int>(0, max<int>(n, min<int>(500, n*(n-1) / 2 + 1)));


		Graph<NoData> g(n);
		g.erdosRenyi(m);
		vector<edge> edges;
		g.forEdges([&](int a, int b){
			ll w = Random::integer<ll>(-1'000'000'000ll, 1'000'000'000ll);
			edges.push_back({a, b, w});
		});

		ll got = kruskal(edges, n);
		ll expected = prim(edges, n);

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 500'000;
constexpr int M = 3'000'000;
void performance_test() {
	timer t;
	Graph<NoData> g(N);
	g.erdosRenyi(M);
	vector<edge> edges;
	g.forEdges([&](int a, int b){
		ll w = Random::integer<ll>(-1'000'000'000ll, 1'000'000'000ll);
		edges.push_back({a, b, w});
	});

	t.start();
	hash_t hash = kruskal(edges, N);
	t.stop();
	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
