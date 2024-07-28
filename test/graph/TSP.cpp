#include "../util.h"
struct edge {
	ll dist;
	int to;
};
constexpr ll INF = LL::INF;
#include <graph/TSP.cpp>

vector<int> naive() {
	int n = sz(dist);
	vector<int> todo(n - 1);
	iota(all(todo), 1);
	vector<int> res;
	ll best = LL::INF;
	do {
		int last = 0;
		ll cur = 0;
		for (int x : todo) {
			cur += dist[last][x];
			last = x;
		}
		cur += dist[last][0];
		if (cur < best) {
			best = cur;
			res = todo;
			res.insert(res.begin(), 0);
			res.push_back(0);
		}
	} while (next_permutation(all(todo)));
	return res;
}

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 100'000; i++) {
		int n = Random::integer<int>(1, 9);
		dist.assign(n, {});
		for (auto& v : dist) v = Random::integers<ll>(n, 0, 1000'000'000);

		auto expected = naive();
		auto got = TSP();
		
		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 19;
void performance_test() {
	timer t;
	dist.assign(N, {});
	for (auto& v : dist) v = Random::integers<ll>(N, 0, 1000'000'000);
	t.start();
	auto got = TSP();
	t.stop();

	hash_t hash = 0;
	for (int x : got) hash += x;
	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
