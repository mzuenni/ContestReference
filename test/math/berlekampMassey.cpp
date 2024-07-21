#include "../util.h"
#include <math/modPowIterativ.cpp>
#include <math/berlekampMassey.cpp>

struct RandomRecurence {
	vector<ll> f, c, cache;
	RandomRecurence(int n) : f(Random::integers<ll>(n, 0, mod)), c(Random::integers<ll>(n, 0, mod)), cache(f) {}
	RandomRecurence(const vector<ll>& f_, const vector<ll>& c_) : c(c_), cache(f_) {
		if (cache.size() < c.size()) cerr << "wrong size" << FAIL;
		cache.resize(c.size());
		f = cache;
	}

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
	for (int i = 0; i < 50'000; i++) {
		int n = Random::integer<int>(1, 10);
		RandomRecurence expected(n);

		ll k = Random::integer<ll>(2*n, 100);
		vector<ll> s(k);
		for (ll j = 0; j < k; j++) s[j] = expected(j);

		auto res = BerlekampMassey(s);
		RandomRecurence got(s, res);

		for (ll j = 0; j < 3*k; j++) {
			if (got(j) != expected(j)) cerr << "got: " << got(j) << ", expected: " << expected(j) << FAIL;
		}

		queries += k;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 5'000;
void performance_test() {
	timer t;
	RandomRecurence f(N);
	f(2*N);
	t.start();
	auto res = BerlekampMassey(f.cache);
	t.stop();
	hash_t hash = 0;
	for (ll x : res) hash += x;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

	
int main() {
	stress_test();
	performance_test();
}

