#include "../util.h"
vector<vector<int>> adj;
#include <graph/centroid.cpp>

int subtreeSize(int c, int p) {
	int res = 1;
	for (int x : adj[c]) {
		if (x == p) continue;
		res += subtreeSize(x, c);
	}
	return res;
}

vector<int> naive() {
	vector<int> res;
	for (int i = 0; i < sz(adj); i++) {
		bool isCentroid = true;
		for (int j : adj[i]) isCentroid &= 2*subtreeSize(j, i) <= sz(adj);
		if (isCentroid) res.push_back(i);
	}
	return res;
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 50);
		Graph<NoData> g(n);
		g.tree();

		adj.assign(n, {});
		g.forEdges([&](int a, int b){
			adj[a].push_back(b);
			adj[b].push_back(a);
		});
		
		auto expected = naive();
		sort(all(expected));

		for (int i = 0; i < n; i++) {
			auto [a, b] = find_centroid(i);
			vector<int> got;
			if (a >= 0) got.push_back(a);
			if (b >= 0) got.push_back(b);
			sort(all(got));

			if (got != expected) cerr << "error" << FAIL;
		}
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 2'000'000;
void performance_test() {
	timer t;
	Graph<NoData> g(N);
	g.tree();

	adj.assign(N, {});
	g.forEdges([&](int a, int b){
		adj[a].push_back(b);
		adj[b].push_back(a);
	});

	t.start();	
	auto [gotA, gotB] = find_centroid();
	t.stop();
	hash_t hash = gotA + gotB;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
