#include "../util.h"
constexpr ll inf = LL::INF;
#include <datastructures/lazyPropagation.cpp>

constexpr int n = 1000'000;

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100; tries++) {
		int n = Random::integer<int>(10, 100);
		vector<ll> naive(n);
		for (ll& x : naive) x = Random::integer<ll>(-1000, 1000);
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
	vector<ll> tmp(n);
	SegTree tree(tmp);
	t.stop();
	ll hash = 0;
	for (int operations = 0; operations < n; operations++) {
		int l1 = Random::integer<int>(0, n + 1);
		int r1 = Random::integer<int>(0, n + 1);
		int l2 = Random::integer<int>(0, n + 1);
		int r2 = Random::integer<int>(0, n + 1);
		if (l1 > r1) swap(l1, r1);
		if (l2 > r2) swap(l2, r2);
		ll x = Random::integer<ll>(-1000, 1000);
		
		t.start();
		tree.update(l1, r1, x);
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
