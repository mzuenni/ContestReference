#include "../util.h"
#include <graph/reroot.cpp>

void stress_test() {
	for (int tries = 0; tries < 50'000; tries++) {
		int n = Random::integer<int>(1, 50);
		Graph<NoData> g(n);
		g.tree();

        adj.assign(n, {});
		g.forEdges([&](int a, int b){
			adj[a].emplace_back(b, Random::integer(0, 10));
			adj[b].emplace_back(a, Random::integer(0, 10));
		});

        Reroot re;
        auto ans = re.solve();

        auto dfs = [&](auto& self, int u, int p) -> ll {
            ll val = 0;
            for (auto [v, w] : adj[u]) if (v != p) {
                val ^= ((v ^ u) + self(self, v, u)) * w % MOD;
            }
            return u ^ val;
        };
        for (int i=0; i<n; i++) {
            if (ans[i] != dfs(dfs, i, -1)) {
                cerr << "WA expected " << dfs(dfs, i, -1) << " got " << ans[i] << FAIL;
            }
        }
	}
	cerr << "tested random 50'000 tests" << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	Graph<NoData> g(N);
	g.tree();
    adj.assign(N, {});
	g.forEdges([&](int a, int b){
        adj[a].emplace_back(b, Random::integer(0, (int)1e9));
        adj[b].emplace_back(a, Random::integer(0, (int)1e9));
	});

    ll hash = 0;
	t.start();
    Reroot re;
    auto ans = re.solve();
    hash = accumulate(all(ans), 0LL);
	t.stop();
	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
