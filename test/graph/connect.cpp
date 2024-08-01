#include "../util.h"
#pragma GCC diagnostic ignored "-Wshadow"
#include "connectMinLCT.h"
constexpr ll INF = 0x3FFF'FFFF;
#include <graph/connect.cpp>

struct Naive {
	vector<multiset<int>> adj;
	vector<int> seen;
	int counter;
	Naive(int n) : adj(n), seen(n), counter(0) {}

	template<typename F>
	void dfs(int x, F&& f) {
		counter++;
		vector<int> todo = {x};
		seen[x] = counter;
		while (!todo.empty()) {
			x = todo.back();
			todo.pop_back();
			f(x);
			for (ll y : adj[x]) {
				if (seen[y] != counter) {
					seen[y] = counter;
					todo.push_back(y);
				}
			}
		}
	}

	bool connected(int a, int b) {
		bool res = false;
		dfs(a, [&](int x){res |= x == b;});
		return res;
	}

	void addEdge(int a, int b) {
		adj[a].insert(b);
		adj[b].insert(a);
	}

	void eraseEdge(int a, int b) {
		adj[a].erase(adj[a].find(b));
		adj[b].erase(adj[b].find(a));
	}
};

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 2'000; tries++) {
		int n = Random::integer<int>(2, 30);
		int m = Random::integer<int>(30, 300);

		vector<int> insertOrder(m);
		iota(all(insertOrder), 0);
		shuffle(all(insertOrder), Random::rng);
		vector<pair<int, int>> edges(m, {-1, -1});

		connect con(n, m);
		Naive naive(n);

		int deleted = 0;
		for (int i = 0; i < m; i++) {
			{
				int a = Random::integer<int>(0, n);
				int b = a;
				while (b == a) b = Random::integer<int>(0, n);
				edges[insertOrder[i]] = {a, b};

				con.addEdge(a, b, insertOrder[i]);
				naive.addEdge(a, b);
			}

			while (deleted < m && edges[deleted] != pair<int, int>{-1, -1} && Random::integer<int>(2) == 0) {
				auto [a, b] = edges[deleted];

				con.eraseEdge(deleted);
				naive.eraseEdge(a, b);
				deleted++;
			}

			for (int j = 0; j < n; j++) {
				int a = Random::integer<int>(0, n);
				int b = Random::integer<int>(0, n);

				auto got = con.connected(a, b);
				auto expected = naive.connected(a, b);

				if (got != expected) cerr << "error" << FAIL;
			}

			queries += n;
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 2'000'000;
void performance_test() {
	/*timer t;
	t.start();
	UF uf(N);
	t.stop();
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		int i = Random::integer<int>(0, N);
		int j = Random::integer<int>(0, N);
		int k = Random::integer<int>(0, N);
		int l = Random::integer<int>(0, N);
		
		t.start();
		uf.unionSets(i, j);
		hash += uf.size(k);
		hash += uf.size(l);
		t.stop();
	}
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;*/
}

int main() {
	stress_test();
	performance_test();
}
