#include "../util.h"
constexpr ll INF = LL::INF;
struct edge {
	int from, to;
	ll cost;
};
#include <graph/bellmannFord.cpp>
namespace floydWarshall {
#include <graph/floydWarshall.cpp>
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(2, 30);
		int m = Random::integer<int>(n-1, max<int>(n, min<int>(500, n*(n-1) / 2 + 1)));
		vector<ll> potential = Random::integers<ll>(n, 0, 1'000'000'000'000ll);

		vector<edge> edges;
		floydWarshall::dist.assign(n, vector<ll>(n, INF));
		for (int i = 0; i < n; i++) floydWarshall::dist[i][i] = 0;

		Graph<NoData, true> g(n);
		g.erdosRenyi(m);
		g.forEdges([&](int a, int b){
			ll w = Random::integer<ll>(1, 100'000'000'000ll);
			w = potential[b] + w - potential[a];
			edges.push_back({a, b, w});
			floydWarshall::dist[a][b] = min(floydWarshall::dist[a][b], w);
		});

		vector<vector<ll>> orig = floydWarshall::dist;

		floydWarshall::floydWarshall();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 10; j++) {
				int k = Random::integer<int>(0, n);
				auto path = floydWarshall::getPath(i, k);
				if (path.empty() != (floydWarshall::dist[i][k] == INF)) cerr << "error: reconstruction" << FAIL;
				if (path.empty()) continue;
				if (path.front() != i) cerr << "error: start" << FAIL;
				if (path.back() != k) cerr << "error: end" << FAIL;
				for (int l = 1; l < sz(path); l++) {
					if (floydWarshall::dist[i][path[l-1]] +
						orig[path[l-1]][path[l]] +
						floydWarshall::dist[path[l]][k] !=
						floydWarshall::dist[i][k]) cerr << "error: edge" << FAIL;
				}
			}
		}

		for (int i = 0; i < n; i++) {
			auto got = floydWarshall::dist[i];
			auto expected = bellmannFord(n, edges, i);
			
			if (got != expected) cerr << "error" << FAIL;
			queries += n;
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 500;
constexpr int M = 20'000;
void performance_test() {
	timer t;
	Graph<NoData> g(N);
	g.erdosRenyi(M);
	floydWarshall::dist.assign(N, vector<ll>(N, INF));
	for (int i = 0; i < N; i++) floydWarshall::dist[i][i] = 0;
	g.forEdges([&](int a, int b){
		ll w1 = Random::integer<ll>(1, 1'000'000'000'000ll);
		ll w2 = Random::integer<ll>(1, 1'000'000'000'000ll);
		floydWarshall::dist[a][b] = w1;
		floydWarshall::dist[b][a] = w2;
	});

	t.start();
	floydWarshall::floydWarshall();
	t.stop();
	hash_t hash = 0;
	for (auto x : floydWarshall::dist[42]) hash += x;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
