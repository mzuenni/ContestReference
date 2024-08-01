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

constexpr int N = 100'000;
constexpr int M = 500'000;
void performance_test() {
	timer t;
	t.start();
	connect con(N, M);
	t.stop();

	vector<int> insertOrder(M);
	iota(all(insertOrder), 0);
	shuffle(all(insertOrder), Random::rng);
	vector<bool> inserted(M);

	for (int i = 0, j = 0; i < N; i++) {
		int a = Random::integer<int>(0, N);
		int b = a;
		while (b == a) b = Random::integer<int>(0, N);
		
		t.start();
		con.addEdge(a, b, insertOrder[i]);
		t.stop();
		inserted[i] = true;

		while (j < M && inserted[j] && Random::integer<int>(2) == 0) {
			t.start();
			con.eraseEdge(j);
			t.stop();
		}
	}
	hash_t hash = 0;
	for (int i = 1; i < N; i++) {
		t.start();
		hash += con.connected(i - 1, i);
		t.stop();
	}
	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
