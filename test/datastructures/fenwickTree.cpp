#include "../util.h"
#include <datastructures/fenwickTree.cpp>

//void update(int i, ll val)
//void init(int n)
//prefix_sum(int i)

void stress_test() {
	ll queries = 0;
	ll hash = 0;
	for (int tries = 0; tries < 100; tries++) {
		int n = Random::integer<int>(10, 100);
		init(n);
		vector<ll> naive(n);
		for (int operations = 0; operations < 1000; operations++) {
			{
				int i = Random::integer<int>(0, n);
				ll x = Random::integer<ll>(-1000, 1000);
				update(i, x);
				naive[i] += x;
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

constexpr int n = 1'000'000;
void performance_test() {
	timer t;
	t.start();
	init(n);
	t.stop();
	ll hash = 0;
	for (int operations = 0; operations < n; operations++) {
		int i = Random::integer<int>(0, n);
		int j = Random::integer<int>(0, n);
		ll x = Random::integer<ll>(-1000, 1000);
		
		t.start();
		update(i, x);
		hash ^= prefix_sum(j);
		t.stop();
	}
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
