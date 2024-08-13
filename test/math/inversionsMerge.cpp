#include "../util.h"
#include <math/inversionsMerge.cpp>

ll naive(const vector<ll>& v) {
	ll res = 0;
	for (ll i = 0; i < sz(v); i++) {
		for (ll j = 0; j < i; j++) {
			if (v[j] > v[i]) res++;
		}
	}
	return res;
}

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 100'000; i++) {
		int n = Random::integer<int>(1, 100);
		vector<ll> v(n);
		for (ll j = 0; j < n; j++) v[j] = (j-10) * 100000 + Random::integer<ll>(0, 10000); //values must be unique ):
		shuffle(all(v), Random::rng);
		ll expected = naive(v);
		ll got = mergeSort(v);
		if (got != expected) {
			cerr << "got: " << got << ", expected: " << expected << FAIL;
		}
		queries += n;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 2'000'000; //10 times faster
void performance_test() {
	timer t;
	auto v = Random::integers<ll>(N, -10'000, 10'000);
	t.start();
	hash_t hash = mergeSort(v);
	t.stop();
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

