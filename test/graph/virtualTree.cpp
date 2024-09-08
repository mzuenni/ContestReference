#include "../util.h"
int lca(int u, int v);
#include <graph/virtualTree.cpp>

vector<int> d, par;
void dfs(int u, vector<vector<int>>& adj, int& counter) {
    in[u] = counter++;
    for (int v : adj[u]) if (v != par[u]) {
        d[v] = d[u]+1;
        par[v] = u;
        dfs(v, adj, counter);
    }
    out[u] = counter;
}

int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    while (d[u] > d[v]) u = par[u];
    while (u != v) u = par[u], v = par[v];
    return u;
}

void init(vector<vector<int>>& adj) {
    int n = (int)sz(adj);
    d.assign(n, 0);
    in = par = out = d;
    int counter = 0;
    dfs(0, adj, counter);
}

void stress_test() {
	for (int tries = 0; tries < 50'000; tries++) {
		int n = Random::integer<int>(1, 50);
		Graph<NoData> g(n);
		g.tree();

		vector<vector<int>> adj(n);
		g.forEdges([&](int a, int b){
			adj[a].push_back(b);
			adj[b].push_back(a);
		});

        init(adj);
        vector<int> ind = Random::distinct(Random::integer(1, n+1), 0, n);
        auto [idk, tree] = virtualTree(ind);
        vector<pair<int, int>> edges;
        for (int i=0; i<sz(idk); i++) for (int v : tree[i]) {
            edges.emplace_back(idk[i], idk[v]);
        }

        vector<pair<int, int>> edges2;
        vector<bool> used(n);
        for (int u : ind) for (int v : ind) used[lca(u, v)] = true;
        auto dfs = [&](auto& self, int u, int p, int last) -> void {
            if (used[u]) {
                if (last != -1) edges2.emplace_back(last, u);
                last = u;
            }
            for (int v : adj[u]) if (v != p) self(self, v, u, last);
        };
        dfs(dfs, 0, -1, -1);

        sort(all(edges)), sort(all(edges2));
        if (edges != edges2) cerr << "WA edge list does not match" << FAIL;
	}
	cerr << "tested random 50'000 tests" << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	Graph<NoData> g(N);
	g.tree();
	vector<vector<int>> adj(N);
	g.forEdges([&](int a, int b){
		adj[a].push_back(b);
		adj[b].push_back(a);
	});

    init(adj);
    vector<int> ind = Random::distinct(N/2, 0, N);

    ll hash = 0;
	t.start();
    auto [idk, tree] = virtualTree(ind);
    hash = accumulate(all(idk), 0LL);
	t.stop();
	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
