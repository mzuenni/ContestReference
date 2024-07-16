#include "../util.h"
struct UF {
	UF(int n) {init(n);}
	#include <datastructures/unionFind.cpp>
};

struct Naive {
	vector<vector<int>> adj;
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

	int findSet(int a) {
		int res = a;
		dfs(a, [&](int x){res = min(res, x);});
		return res;
	}

	void unionSets(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	int size(int a) {
		int res = 0;
		dfs(a, [&](int /**/){res++;});
		return res;
	}
};

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 200; tries++) {
		int n = Random::integer<int>(1, 100);
		UF uf(n);
		Naive naive(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 10; j++) {
				int a = Random::integer<int>(0, n);
				int b = Random::integer<int>(0, n);
				uf.unionSets(a, b);
				naive.unionSets(a, b);
			}
			UF tmp = uf;
			for (int j = 0; j < n; j++) {
				{
					auto got = tmp.size(j);
					auto expected = naive.size(j);
					if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
				}
				{
					int a = Random::integer<int>(0, n);
					int b = Random::integer<int>(0, n);
					bool got = tmp.findSet(a) == tmp.findSet(b);
					bool expected = naive.findSet(a) == naive.findSet(b);
					if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
				}
			}
			queries += n;
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 2'000'000;
void performance_test() {
	timer t;
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
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
