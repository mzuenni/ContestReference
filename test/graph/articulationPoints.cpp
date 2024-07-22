#include "../util.h"
struct edge {
	ll from, to, id;
};
#define Edge edge
#include <graph/articulationPoints.cpp>
#undef Edge

vector<bool> naiveArt() {
	vector<bool> res(sz(adj));

	vector<int> seen(sz(adj), -1);
	for (int i = 0; i < sz(adj); i++) {
		if (adj[i].empty()) continue;
		seen[i] = i;
		vector<ll> todo = {adj[i][0].to};
		seen[todo[0]] = i;
		while (!todo.empty()) {
			int c = todo.back();
			todo.pop_back();
			for (auto e : adj[c]) {
				if (seen[e.to] == i) continue;
				seen[e.to] = i;
				todo.push_back(e.to);
			}
		}
		for (auto e : adj[i]) {
			if (seen[e.to] != i) res[i] = true;
		}
	}
	return res;
}

void stress_test_art() {
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

		auto expected = naiveArt();
		find();
		vector<bool> got = isArt;

		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 500'000;
constexpr int M = 2'000'000;
void performance_test() {
	timer t;
	Graph<NoData, 0, 1> g(N);
	g.erdosRenyi(M);
	adj.assign(N, {});
	int nextId = 0;
	g.forEdges([&](int a, int b){
		adj[a].push_back({a, b, nextId});
		adj[b].push_back({b, a, nextId});
		nextId++;
	});

	t.start();
	find();	
	t.stop();
	hash_t hash = sz(bridges) + sz(bcc);
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test_art();
	performance_test();
}
