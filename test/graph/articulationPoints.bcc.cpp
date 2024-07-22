#include "../util.h"
struct edge {
	ll from, to, id;
};
#define Edge edge
#include <graph/articulationPoints.cpp>
#undef Edge
#include <datastructures/unionFind.cpp>

vector<vector<int>> naiveBCC(int m) {
	init(m);

	vector<int> seen(sz(adj), -1);
	int run = 0;
	for (int i = 0; i < sz(adj); i++) {
		for (auto e : adj[i]) {
			run++;
			seen[i] = run;
			vector<ll> todo = {e.to};
			seen[e.to] = run;
			while (!todo.empty()) {
				int c = todo.back();
				todo.pop_back();
				for (auto ee : adj[c]) {
					if (seen[ee.to] == run) continue;
					seen[ee.to] = run;
					todo.push_back(ee.to);
				}
			}
			for (auto ee : adj[i]) {
				if (seen[ee.to] == run) unionSets(ee.id, e.id);
			}
		}
	}
	vector<vector<int>> res(m);
	for (int i = 0; i < m; i++) {
		res[findSet(i)].push_back(i);
	}
	for (auto& v : res) sort(all(v));
	res.erase(remove_if(all(res), [](const vector<int>& v){return sz(v) <= 1;}), res.end());
	sort(all(res));
	return res;
}

void stress_test_bcc() {
	ll queries = 0;
	for (int tries = 0; tries < 200'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(0, max<int>(1, min<int>(300, n*(n-1) / 2 + 1)));
		Graph<NoData, 0, 1> g(n);
		g.erdosRenyi(m);

		adj.assign(n, {});
		int nextId = 0;
		g.forEdges([&](int a, int b){
			adj[a].push_back({a, b, nextId});
			adj[b].push_back({b, a, nextId});
			nextId++;
		});

		auto expected = naiveBCC(nextId);
		find();
		vector<vector<int>> got(sz(bcc));
		for (int i = 0; i < sz(bcc); i++) {
			for (auto e : bcc[i]) got[i].push_back(e.id);
			sort(all(got[i]));
		}
		sort(all(got));

		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

int main() {
	stress_test_bcc();
}
