#include "../util.h"
struct edge {
	ll from, to, id;
};
#define Edge edge
#include <graph/articulationPoints.cpp>
#undef Edge

vector<bool> naiveBridges(const vector<pair<int, int>>& edges) {
	vector<bool> res(sz(edges));

	vector<int> seen(sz(adj), -1);
	for (int i = 0; i < sz(edges); i++) {
		auto [a, b] = edges[i];
		vector<int> todo = {a};
		seen[a] = i;
		while (!todo.empty() && seen[b] != i) {
			int c = todo.back();
			todo.pop_back();
			for (auto e : adj[c]) {
				if (e.id == i) continue;
				if (seen[e.to] == i) continue;
				seen[e.to] = i;
				todo.push_back(e.to);
			}
		}
		res[i] = seen[b] != i;
	}
	return res;
}

void stress_test_bridges() {
	ll queries = 0;
	for (int tries = 0; tries < 200'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(0, max<int>(1, min<int>(300, n*(n-1) / 2 + 1)));
		Graph<NoData, 0, 1> g(n);
		g.erdosRenyi(m);

		adj.assign(n, {});
		vector<pair<int, int>> edges;
		g.forEdges([&](int a, int b){
			adj[a].push_back({a, b, sz(edges)});
			adj[b].push_back({b, a, sz(edges)});
			edges.emplace_back(a, b);
		});

		auto expected = naiveBridges(edges);
		find();
		vector<bool> got(sz(edges));
		for (auto e : bridges) {
			if (got[e.id]) cerr << "error: duclicate" << FAIL;
			got[e.id] = true;
		}

		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

int main() {
	stress_test_bridges();
}
