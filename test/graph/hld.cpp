#include "../util.h"
#include <graph/hld.cpp>

struct Seg { // very real segment tree
    vector<int> a;

    Seg(int n) : a(n) {}
    
    void inc(int l, int r) {
        for (int i=l; i<r; i++) a[i]++;
    }
};

void stress_test() {
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 50);
		Graph<NoData> g(n);
		g.tree();

        adj.assign(n, {});
		g.forEdges([&](int a, int b){
			adj[a].push_back(b);
			adj[b].push_back(a);
		});

        init(Random::integer(0, n));

        vector<int> a(n);
        auto dfs = [&](auto& self, int u, int p, int t) {
            if (u == t) {
                a[u]++;
                return true;
            }
            for (int v : adj[u]) if (v != p) {
                if (self(self, v, u, t)) {
                    a[u]++;
                    return true;
                }
            }
            return false;
        };

        Seg seg(n);

        int Q = Random::integer(1, 50);
        for (int q=0; q<Q; q++) {
            int u = Random::integer(0, n), v = Random::integer(0, n);
            for_intervals(u, v, [&](int l, int r) { seg.inc(l, r); });
            dfs(dfs, u, -1, v);
        }
        for (int i=0; i<n; i++) {
            if (seg.a[in[i]] != a[i]) cerr << "WA: expected " << a[i] << " got " << seg.a[in[i]] << FAIL;
        }
	}
	cerr << "tested random tests: " << 100'000 << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	Graph<NoData> g(N);
	g.tree();
    adj.assign(N, {});
	g.forEdges([&](int a, int b){
		adj[a].push_back(b);
		adj[b].push_back(a);
	});
    vector<pair<int, int>> qu(N);
    for (auto& [x, y] : qu) x = Random::integer(0, N), y = Random::integer(0, N);

    ll hash = 0;
	t.start();
    init(0);
    for (auto [x, y] : qu) for_intervals(x, y, [&](int l, int r){ hash += r-l; });
	t.stop();
	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
    performance_test();
}
