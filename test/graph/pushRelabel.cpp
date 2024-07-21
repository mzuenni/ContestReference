#include "../util.h"
namespace dinic {
#include <graph/dinicScaling.cpp>
}

namespace pushRelabel {
#include <graph/pushRelabel.cpp>
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 20'000; tries++) {
		int n = Random::integer<int>(2, 30);
		int m = Random::integer<int>(n-1, max<int>(n, min<int>(500, n*(n-1) / 2 + 1)));

		dinic::adj.assign(n, {});
		pushRelabel::adj.assign(n, {});

		Graph<NoData, true> g(n);
		g.erdosRenyi(m);
		g.forEdges([](int a, int b){
			ll w = Random::integer<ll>(1, 1'000'000'000'000ll);
			dinic::addEdge(a, b, w);
			pushRelabel::addEdge(a, b, w);
		});

		ll got = pushRelabel::maxFlow(0, n - 1);
		ll expected = dinic::maxFlow(0, n - 1);
		
		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 50000;
constexpr int M = 200000;
void performance_test() {
	using namespace pushRelabel;
	timer t;
	Graph<NoData> g(N);
	g.erdosRenyi(M);
	adj.assign(N, {});
	g.forEdges([](int a, int b){
		ll w1 = Random::integer<ll>(1, 1'000'000'000'000ll);
		ll w2 = Random::integer<ll>(1, 1'000'000'000'000ll);
		addEdge(a, b, w1);
		addEdge(b, a, w2);
	});

	t.start();
	hash_t hash = maxFlow(0, N - 1);
	t.stop();
	if (t.time > 300) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
