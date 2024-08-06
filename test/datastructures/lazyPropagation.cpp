#include "../util.h"
constexpr ll INF = LL::INF;
#include <datastructures/lazyPropagation.cpp>

constexpr int N = 1000'000;

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100; tries++) {
		int n = Random::integer<int>(10, 100);
		vector<ll> naive = Random::integers<ll>(n, -1000, 1000);
		SegTree tree(naive);
		for (int operations = 0; operations < 1000; operations++) {
			{
				int l = Random::integer<int>(0, n + 1);
				int r = Random::integer<int>(0, n + 1);
				//if (l > r) swap(l, r);
				ll x = Random::integer<ll>(-1000, 1000);
				tree.update(l, r, x);
				for (int j = l; j < r; j++) naive[j] = x;
			}
			{
				queries++;
				int l = Random::integer<int>(0, n + 1);
				int r = Random::integer<int>(0, n + 1);
				//if (l > r) swap(l, r);
				ll got = tree.query(l, r);
				ll expected = 0;
				for (int j = l; j < r; j++) expected += naive[j];
				if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
			}
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

void performance_test() {
	timer t;
	t.start();
	vector<ll> tmp(N);
	SegTree tree(tmp);
	t.stop();
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		auto [l1, r1] = Random::pair<int>(0, N + 1);
		auto [l2, r2] = Random::pair<int>(0, N + 1);
		ll x1 = Random::integer<ll>(-1000, 1000);
		
		t.start();
		tree.update(l1, r1, x1);
		hash ^= tree.query(l2, r2);
		t.stop();
	}
	if (t.time > 2000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
