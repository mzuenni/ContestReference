#include "../util.h"
#include <datastructures/waveletTree.cpp>

constexpr int N = 1000'000;

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100; tries++) {
		int n = Random::integer<int>(10, 100);
		vector<ll> naive = Random::integers<ll>(n, -1000, 1000);
		WaveletTree tree(naive);
		for (int operations = 0; operations < 1000; operations++) {
			{
				queries++;
				int l = Random::integer<int>(0, n + 1);
				int r = Random::integer<int>(0, n + 1);
				//if (l > r) swap(l, r);
				int x = Random::integer<int>(-1, n);
				ll got = tree.kth(l, r, x);
				ll expected = -1;
				if (x >= 0 && l + x < r) {
					vector<ll> tmp(naive.begin() + l, naive.begin() + r);
					std::sort(all(tmp));
					expected = tmp[x];
				}
				if (got != expected) {
					cerr << "kth, got: " << got << ", expected: " << expected << FAIL;
				}
			}
			{
				queries++;
				int l = Random::integer<int>(0, n + 1);
				int r = Random::integer<int>(0, n + 1);
				//if (l > r) swap(l, r);
				ll x = Random::integer<ll>(-1000, 1000);
				ll got = tree.countSmaller(l, r, x);
				ll expected = 0;
				for (int j = l; j < r; j++) {
					if (naive[j] < x) expected++;
				}
				if (got != expected) {
					cerr << "count, got: " << got << ", expected: " << expected << FAIL;
				}
			}
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

void performance_test() {
	timer t;
	vector<ll> tmp = Random::integers<ll>(N, -1000, 1000);
	t.start();
	WaveletTree tree(tmp);
	t.stop();
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		auto [l1, r1] = Random::pair<int>(0, N + 1);
		auto [l2, r2] = Random::pair<int>(0, N + 1);
		int x1 = Random::integer<ll>(l1, r1 + 1);
		ll x2 = Random::integer<ll>(-1000, 1000);
		
		t.start();
		hash ^= tree.kth(l1, r1, x1);
		hash ^= tree.countSmaller(l2, r2, x2);
		t.stop();
	}
	if (t.time > 2000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
