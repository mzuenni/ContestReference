#include "../util.h"

constexpr ll mod = 1'394'633'899;

struct mat {
	vector<vector<ll>> m;
	mat(int dim = 0, int diag = 1) : m(dim, vector<ll>(dim)) {
		for (int i = 0; i < dim; i++) m[i][i] = diag;
	}
	mat(const vector<ll> c) : m(sz(c), vector<ll>(sz(c))) {
		m[0] = c;
		for (ll i = 1; i < sz(c); i++) {
			m[i][i-1] = 1;
		}
	}

	mat operator*(const mat& o) const {
		int dim = sz(m);
		mat res(dim, 0);
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				for (int k = 0; k < dim; k++) {
					res.m[i][j] += m[i][k] * o.m[k][j];
					res.m[i][j] %= mod;
				}
			}
		}
		return res;
	}

	vector<ll> operator*(const vector<ll>& o) const {
		int dim = sz(m);
		vector<ll> res(dim);
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				res[i] += m[i][j] * o[j];
				res[i] %= mod;
			}
		}
		return res;
	}
};

#include <math/matrixPower.cpp>

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
		precalc(mat(f.c));
		auto tmp = f.f;
		reverse(all(tmp));

		for (int j = 0; j < 100; j++) {
			ll k = Random::integer<ll>(0, 1000);

			vector<ll> got = calc(k, tmp);
			vector<ll> expected(sz(f.f));
			for (ll l = 0; l < n; l++) expected[n - 1 - l] = f(k + l);

			if (got != expected) cerr << "error" << FAIL;
			queries++;
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 100;
constexpr int M = 500;
void performance_test() {
	timer t;
	RandomRecurence f(N);
	auto tmp = f.f;
	reverse(all(tmp));

	t.start();
	precalc(mat(f.c));
	t.stop();
	if (t.time > 500) cerr << "too slow precalc: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms" << endl;

	t.reset();
	hash_t hash = 0;
	for (int i = 0; i < M; i++) {
		ll k = Random::integer<ll>(1e17,1e18);
		t.start();
		hash += calc(k, tmp).back();
		t.stop();
	}
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

