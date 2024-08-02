#include "../util.h"
#pragma GCC diagnostic ignored "-Wshadow"
#include <datastructures/LCT.cpp>

struct Naive {
	vector<set<int>> adj;
	vector<ll> weight;
	Naive(int n) : adj(n), weight(n, queryDefault) {}

	pair<ll, bool> dfs_path(int from, int to, ll delta = queryDefault, int prev = -1) {
		if (from == to) {
			weight[from] += delta;
			return {weight[from], true};
		}
		for (int x : adj[from]) {
			if (x == prev) continue;
			auto [res, seen] = dfs_path(x, to, delta, from);
			if (seen) {
				weight[from] += delta;
				return {res + weight[from], true};
			}
		}
		return {queryDefault, false};
	}

	bool connected(int x, int y) {
		return dfs_path(x, y).second;
	}

	void link(int x, int y) {
		adj[x].insert(y);
		adj[y].insert(x);
	}

	void cut(int x, int y) {
		adj[x].erase(y);
		adj[y].erase(x);
	}

	int lca(int root, int a, int b) {
		int res = -1;
		auto dfs_lca = [&](auto&& self, int c, int prev = -1) -> pair<bool, bool>{
			bool seenA = c == a;
			bool seenB = c == b;
			for (int x : adj[c]) {
				if (x == prev) continue;
				auto [tmpA, tmpB] = self(self, x, c);
				seenA |= tmpA;
				seenB |= tmpB;
			}
			if (seenA && seenB && res < 0) res = c;
			return {seenA, seenB};
		};
		dfs_lca(dfs_lca, root);
		return res;
	}

	ll query(int from, int to) {
		return dfs_path(from, to).first;
	}

	void modify(int from, int to, ll delta) {
		dfs_path(from, to, delta);
	}

	int random(int x) {
		vector<int> seen;
		auto dfs_comp = [&](auto&& self, int c, int prev = -1) -> void {
			seen.push_back(c);
			for (int x : adj[c]) {
				if (x == prev) continue;
				self(self, x, c);
			}
		};
		dfs_comp(dfs_comp, x);
		return seen[Random::integer<int>(sz(seen))];
	}

	int randomAdj(int x) {
		if (adj[x].empty()) return -1;
		vector<int> seen(all(adj[x]));
		return seen[Random::integer<int>(sz(seen))];
	}
};

void stress_test() {
	ll queries = 0;
	ll connected = 0;
	ll link = 0;
	ll lca = 0;
	ll sum = 0;
	ll modify = 0;
	ll cut = 0;
	for (int tries = 0; tries < 500; tries++) {
		int n = Random::integer<int>(1, 100);
		int m = Random::integer<int>(100, 10'000);

		LCT lct(n);
		Naive naive(n);
		for (int i = 0; i < m; i++) {
			bool testConnected = Random::integer<int>(2) == 0;
			bool testLink = Random::integer<int>(2) == 0;
			bool testLCA = Random::integer<int>(2) == 0;
			bool testSum = Random::integer<int>(2) == 0;
			bool testModify = Random::integer<int>(2) == 0;
			bool testCut = Random::integer<int>(2) == 0;

			{
				int a = Random::integer<int>(0, n);
				int b = Random::integer<int>(0, n);

				auto expected = naive.connected(a, b);
				if (testConnected) {
					connected++;
					auto got = lct.connected(&lct.nodes[a], &lct.nodes[b]);
					if (got != expected) cerr << "error: 1" << FAIL;
				}

				if (!expected && testLink) {
					lct.link(&lct.nodes[a], &lct.nodes[b]);
					naive.link(a, b);
					link++;
					expected = true;
				}

				if (testLCA && expected) {
					int c = naive.random(a);
					lct.makeRoot(&lct.nodes[c]);
					auto gotLCA = lct.lca(&lct.nodes[a], &lct.nodes[b])->id;
					auto expectedLCA = naive.lca(c, a, b);
					if (gotLCA != expectedLCA) cerr << "error: 2" << FAIL;
					lca++;
				}

				if (testSum && expected) {
					auto gotSum = lct.query(&lct.nodes[a], &lct.nodes[b]);
					auto expectedSum = naive.query(a, b);
					if (gotSum != expectedSum) cerr << "error: 3" << FAIL;
					sum++;
				}

				if (testModify && expected) {
					ll w = Random::integer<ll>(-1000, 1000);
					lct.modify(&lct.nodes[a], &lct.nodes[b], w);//must a and b directly connected??
					naive.modify(a, b, w);
					modify++;
				}
			}
			{
				int a = Random::integer<int>(0, n);
				int b = naive.randomAdj(a);
				if (b >= 0 && testCut) {
					lct.cut(&lct.nodes[a], &lct.nodes[b]);
					naive.cut(a, b);
					cut++;
				}
			}
			queries++;
		}
	}
	cerr << "tested random queries: " << queries << endl;
	cerr << "  connected: " << connected << endl;
	cerr << "  link: " << link << endl;
	cerr << "  lca: " << lca << endl;
	cerr << "  sum: " << sum << endl;
	cerr << "  modify: " << modify << endl;
	cerr << "  cut: " << cut << endl;
}

constexpr int N = 200'000;
constexpr int M = 500'000;
void performance_test() {
	timer t;
	t.start();
	LCT lct(N);
	t.stop();
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		int a = Random::integer<int>(0, N);
		int b = Random::integer<int>(0, N);
		ll w = Random::integer<ll>(-1000, 1000);
		
		t.start();
		if (!lct.connected(&lct.nodes[a], &lct.nodes[b])) {
			lct.link(&lct.nodes[a], &lct.nodes[b]);
		}
		lct.modify(&lct.nodes[a], &lct.nodes[b], w);
		hash += lct.query(&lct.nodes[a], &lct.nodes[b]);
		t.stop();
	}
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
