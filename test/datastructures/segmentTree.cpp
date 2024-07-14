#include "../util.h"
#include <datastructures/segmentTree.cpp>

constexpr int N = 1'000'000;

//void update(int i, ll val)
//ll query(int l, int r)

//point update + range query
void stress_test1() {
	ll queries = 0;
	for (int tries = 0; tries < 100; tries++) {
		int n = Random::integer<int>(10, 100);
		vector<ll> naive = Random::integers<ll>(n, -1000, 1000);
		SegTree tree(naive);
		for (int operations = 0; operations < 1000; operations++) {
			{
				int i = Random::integer<int>(0, n);
				ll x = Random::integer<ll>(-1000, 1000);
				tree.update(i, x);
				naive[i] = x;//point assignment
			}
			{
				queries++;
				int l = Random::integer<int>(0, n + 1);
				int r = Random::integer<int>(0, n + 1);
				//if (l > r) swap(l, r);
				ll got = tree.query(l, r);
				ll expected = 0;
				for (int j = l; j < r; j++) expected += naive[j];//range sum
				if (got != expected) cerr << "  got: " << got << ", expected: " << expected << FAIL;
			}
		}
	}
	cerr << "  tested random queries: " << queries << endl;
}

//point update + range query
void performance_test1() {
	timer t;
	t.start();
	vector<ll> tmp(N);
	SegTree tree(tmp);
	t.stop();
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		int i = Random::integer<int>(0, N);
		auto [l, r] = Random::pair<int>(0, N + 1);
		ll x = Random::integer<ll>(-1000, 1000);
		
		t.start();
		tree.update(i, x);
		hash ^= tree.query(l, r);
		t.stop();
	}
	if (t.time > 1000) cerr << "  too slow: " << t.time << FAIL;
	cerr << "  tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

//void modify(int l, int r, T val)
//ll query(int i)

//range update + point query
void stress_test2() {
	ll queries = 0;
	for (int tries = 0; tries < 100; tries++) {
		int n = Random::integer<int>(10, 100);
		vector<ll> naive(n);
		SegTree tree(naive);
		naive = Random::integers<ll>(n, -1000, 1000);
		copy(all(naive), tree.tree.begin() + n);
		for (int operations = 0; operations < 1000; operations++) {
			{
				int l = Random::integer<int>(0, n + 1);
				int r = Random::integer<int>(0, n + 1);
				//if (l > r) swap(l, r);
				ll x = Random::integer<ll>(-1000, 1000);
				tree.modify(l, r, x);
				for (int j = l; j < r; j++) naive[j] += x;//range add
			}
			{
				queries++;
				int i = Random::integer<int>(0, n);
				ll got = tree.query(i);
				ll expected = naive[i];//point query
				if (got != expected) cerr << "  got: " << got << ", expected: " << expected << FAIL;
			}
		}
	}
	cerr << "  tested random queries: " << queries << endl;
}

//range update + point query
void performance_test2() {
	timer t;
	t.start();
	vector<ll> tmp(N);
	SegTree tree(tmp);
	t.stop();
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		int i = Random::integer<int>(0, N);
		auto [l, r] = Random::pair<int>(0, N + 1);
		ll x = Random::integer<ll>(-1000, 1000);
		
		t.start();
		tree.modify(l, r, x);
		hash ^= tree.query(i);
		t.stop();
	}
	if (t.time > 1000) cerr << "  too slow: " << t.time << FAIL;
	cerr << "  tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	cerr << "point update + range query:" << endl;
	stress_test1();
	performance_test1();
	cerr << "range update + point query" << endl;
	stress_test2();
	performance_test2();
}
