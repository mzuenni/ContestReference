#include "../util.h"
#include <math/linearRecurrenceOld.cpp>

struct RandomRecurence {
	vector<ll> f, c, cache;
	RandomRecurence(int n) : f(Random::integers<ll>(n, 0, mod)), c(Random::integers<ll>(n, 0, mod)), cache(f) {}

	ll operator()(ll k){
		while (sz(cache) <= k) {
			ll cur = 0;
			for (ll i = 0; i < sz(c); i++) {
				cur += (c[i] * cache[sz(cache) - i - 1]) % mod;
			}
			cur %= mod;
			cache.push_back(cur);
		}
		return cache[k];
	}
};

void stress_test() {
	int queries = 0;
	for (int i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 10);
		RandomRecurence f(n);
		for (int j = 0; j < 100; j++) {
			ll k = Random::integer<ll>(0, 1000);

			ll got = kthTerm(f.f, f.c, k);
			ll expected = f(k);

			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
			queries++;
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 1'000;
void performance_test() {
	timer t;
	RandomRecurence f(N);
	t.start();
	hash_t hash = kthTerm(f.f, f.c, 1e18);
	t.stop();
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

