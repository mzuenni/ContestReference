#include "../util.h"
constexpr ll INF = LL::INF;

namespace stoerWagner {
#include <graph/stoerWagner.cpp>
	void addEdge(int u, int v, ll c) {
		adj[u].push_back({u, v, c});
		adj[v].push_back({v, u, c});
	}
}

namespace pushRelabel {
#include <graph/pushRelabel.cpp>
	ll minCut() {
		ll res = INF;
		for (int i = 0; i < sz(adj); i++) {
			for (int j = 0; j < i; j++) {
				if (i == j) continue;
				res = min(res, maxFlow(i, j));
				for (auto& v : adj) {
					for (auto& e : v) {
						e.f = 0;
					}
				}
			}
		}
		return res;
	}
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 5'000; tries++) {
		int n = Random::integer<int>(2, 30);
		int m = Random::integer<int>(n-1, max<int>(n, min<int>(500, n*(n-1) / 2 + 1)));

		stoerWagner::adj.assign(n, {});
		pushRelabel::adj.assign(n, {});

		Graph<NoData> g(n);
		g.erdosRenyi(m);
		g.forEdges([](int a, int b){
			ll w = Random::integer<ll>(1, 1'000'000'000'000ll);
			stoerWagner::addEdge(a, b, w);
			pushRelabel::addEdge(a, b, w);
			pushRelabel::addEdge(b, a, w);
		});

		ll got = stoerWagner::stoer_wagner();
		ll expected = pushRelabel::minCut();
		
		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 200;
constexpr int M = 10000;
void performance_test() {
	using namespace stoerWagner;
	timer t;
	Graph<NoData> g(N);
	g.erdosRenyi(M);
	adj.assign(N, {});
	g.forEdges([](int a, int b){
		ll w = Random::integer<ll>(1, 1'000'000'000'000ll);
		addEdge(a, b, w);
	});

	t.start();
	hash_t hash = stoer_wagner();
	t.stop();
	if (t.time > 2000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
