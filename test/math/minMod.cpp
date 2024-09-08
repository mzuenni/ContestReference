#include "../util.h"
#include <math/shortModInv.cpp>
#include <math/minMod.cpp>

ll naiveMinMod(ll n, ll m, ll a, ll b){
	ll ans = m;
	for(ll i = 0; i < n; i++){
		ans = min(ans, (a*i+b)%m);
	}
	return ans;
}

ll naiveFirstVal(ll a, ll m, ll l, ll r){
	for(ll i = 0; i < m; i++){
		ll v = a*i % m;
		if(l <= v && v <= r) return v;
	}
	return -1;
}

void stress_test_minMod() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 100);
		int m = Random::integer<int>(1, 100);
		int a = Random::integer<int>(0, m);
		int b = Random::integer<int>(0, m);
		ll expected = naiveMinMod(n, m, a, b);
		ll got = minMod(n, m, a, b);
		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested queries: " << queries << endl;
}

void stress_test_firstVal() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int m = Random::integer<int>(1, 100);
		int a = Random::integer<int>(0, m);
		int l = Random::integer<int>(0, m);
		int r = Random::integer<int>(0, m);
		if(l > r) swap(l, r);
		ll expected = naiveFirstVal(a, m, l, r);
		ll got = firstVal(a, m, l, r);
		if (got != expected) cerr << a << " " << m << " " << l << " " << r << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 1'000'000;
void performance_test_minMod() {
	timer t;
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll n = Random::integer<ll>(1, 1'000'000'000);
		ll m = Random::integer<ll>(1, 1'000'000'000);
		ll a = Random::integer<ll>(0, m);
		ll b = Random::integer<ll>(0, m);
		t.start();
		hash += minMod(n, m, a, b);
		t.stop();
	}
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

void performance_test_firstVal() {
	timer t;
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll m = Random::integer<ll>(1, 1'000'000'000);
		ll a = Random::integer<ll>(1, m);
		ll l = Random::integer<ll>(0, m);
		ll r = Random::integer<ll>(0, m);
		if(l > r) swap(l, r);
		t.start();
		hash += firstVal(a, m, l, r);
		t.stop();
	}
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test_minMod();
	stress_test_firstVal();
	performance_test_minMod();
	performance_test_firstVal();
}

