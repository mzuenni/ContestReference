#include "../util.h"
#include <datastructures/fenwickTree2.cpp>

//void update(int l, int r, ll val)
//void init(int n)
//prefix_sum(int i)

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100; tries++) {
		int n = Random::integer<int>(10, 100);
		vector<ll> naive(n);// = Random::integers<ll>(n, -1000, 1000);
		init(naive);
		for (int operations = 0; operations < 1000; operations++) {
			{
				auto [i, j] = Random::pair<int>(0, n);
				ll x = Random::integer<ll>(-1000, 1000);
				update(i, j, x);
				for (int k = i; k < j; k++) naive[k] += x;
			}
			{
				queries++;
				int i = Random::integer<int>(0, n);
				ll got = prefix_sum(i);
				ll expected = 0;
				for (int j = 0; j <= i; j++) expected += naive[j];
				if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
			}
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	vector<ll> tmp = Random::integers<ll>(N, -1000, 1000);
	t.start();
	init(tmp);
	t.stop();
	ll hash = 0;
	for (int operations = 0; operations < N; operations++) {
		int i = Random::integer<int>(0, N);
		int j = Random::integer<int>(0, N);
		int k = Random::integer<int>(0, N);
		ll x = Random::integer<ll>(-1000, 1000);
		
		t.start();
		update(i, j, x);
		hash ^= prefix_sum(k);
		t.stop();
	}
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
