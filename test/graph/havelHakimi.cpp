#include "../util.h"
#include <graph/havelHakimi.cpp>

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 200'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(0, n*(n-1) / 2 + 1);
		Graph g(n);
		g.erdosRenyi(m);

		vector<int> expected(n);
		for (int i = 0; i < n; i++) expected[i] = g.deg(i);

		auto res = havelHakimi(expected);
		if (sz(res) != n) cerr << "error: wrong number of nodes" << FAIL;
		vector<vector<int>> rev(n);
		vector<int> got(n);
		for (int i = 0; i < n; i++) {
			got[i] = sz(res[i]);
			for (int j : res[i]) {
				if (j < 0 || j >= n) cerr << "error: invalid edge" << FAIL;
				rev[j].push_back(i);
			}
		}

		for (int i = 0; i < n; i++) {
			sort(all(res[i]));
			sort(all(rev[i]));
			if (res[i] != rev[i]) cerr << "error: graph is directed" << FAIL;
			for (int j : res[i]) if (j == i) cerr << "error: graph has loop" << FAIL;
			for (int j = 1; j < sz(res[i]); j++) {
				if (res[i][j] == res[i][j-1]) cerr << "error: multiedge" << FAIL;
			}
		}

		if (expected != got) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 200'000;
constexpr int M = 1'000'000;
void performance_test() {
	timer t;
	Graph g(N);
	g.erdosRenyi(M);

	vector<int> expected(N);
	for (int i = 0; i < N; i++) expected[i] = g.deg(i);

	t.start();
	auto res = havelHakimi(expected);
	t.stop();
	hash_t hash = 0;
	for (auto& v : res) hash += sz(v);
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
