#include "../util.h"
struct tree {
	tree(int n) : adj(n) {}
	#include <graph/treeIsomorphism.cpp>
	#include <graph/centroid.cpp>

	pair<int, int> treeLabel() {
		auto [a, b] = find_centroid(0);
		if (a >= 0) a = treeLabel(a);
		if (b >= 0) b = treeLabel(b);
		if (a > b) swap(a, b);
		return {a, b};
	}
};

void stress_test_eq() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 50);
		Graph<NoData> g(n);
		g.tree();

		tree t(n);

		g.forEdges([&](int a, int b){
			t.adj[a].push_back(b);
			t.adj[b].push_back(a);
		});
		auto [gotA, gotB] = t.treeLabel();

		g.permutate();
		t.adj.assign(n, {});
		g.forEdges([&](int a, int b){
			t.adj[a].push_back(b);
			t.adj[b].push_back(a);
		});
		auto [expectedA, expectedB] = t.treeLabel();

		if (gotA != expectedA) cerr << "got: " << gotA << ", expected: " << expectedA << FAIL;
		if (gotB != expectedB) cerr << "got: " << gotB << ", expected: " << expectedB << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

void test_tiny() {
	vector<int> expected = {1,1,1,1,2,3,6,11,23}; //#A000055
	for (int i = 1; i < sz(expected); i++) {
		set<pair<int, int>> got;
		tree t(i);

		int labeled = 1;
		for (int j = 3; j < i; j++) labeled *= i;
		for (int j = 0; j < 10 * labeled; j++) {
			Graph<NoData> g(i);
			g.tree();

			t.adj.assign(i, {});
			g.forEdges([&](int a, int b){
				t.adj[a].push_back(b);
				t.adj[b].push_back(a);
			});

			got.insert(t.treeLabel());
		}
		if (sz(got) != expected[i]) cerr << i << ", got: " << sz(got) << ", expected: " << expected[i] << FAIL;
	}
	cerr << "tested tiny: " << sz(expected) << endl;
}

void stress_test_neq() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(20, 50);
		Graph<NoData> g(n);
		g.tree();

		tree t(n);

		g.forEdges([&](int a, int b){
			t.adj[a].push_back(b);
			t.adj[b].push_back(a);
		});
		auto [gotA, gotB] = t.treeLabel();

		g.clear().tree();
		t.adj.assign(n, {});
		g.forEdges([&](int a, int b){
			t.adj[a].push_back(b);
			t.adj[b].push_back(a);
		});
		auto [expectedA, expectedB] = t.treeLabel();

		if (gotA == expectedA && gotA >= 0) cerr << "error: " << n << ", " << tries << FAIL;
		if (gotB == expectedB) cerr << "error: " << n << ", " << tries << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 500'000;
void performance_test() {
	timer t;
	Graph<NoData> g(N);
	g.tree();

	tree tt(N);
	g.forEdges([&](int a, int b){
		tt.adj[a].push_back(b);
		tt.adj[b].push_back(a);
	});

	t.start();	
	auto [gotA, gotB] = tt.treeLabel();
	t.stop();
	hash_t hash = gotA + gotB;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test_eq();
	test_tiny();
	stress_test_neq();
	performance_test();
}
