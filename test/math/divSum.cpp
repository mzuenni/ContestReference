#include "../util.h"
#include <math/divSum.cpp>

ll naive(ll n, ll m, ll a, ll b){
	ll ans = 0;
	for(ll i = 0; i < n; i++){
		ans += (a*i+b)/m;
	}
	return ans;
}

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 100);
		int m = Random::integer<int>(1, 100);
		int a = Random::integer<int>(0, 100);
		int b = Random::integer<int>(0, 100);
		ll expected = naive(n, m, a, b);
		ll got = divSum(n, m, a, b);
		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll n = Random::integer<ll>(1, 1'000'000'000);
		ll m = Random::integer<ll>(1, 1'000'000'000);
		ll a = Random::integer<ll>(0, 1'000'000'000);
		ll b = Random::integer<ll>(0, 1'000'000'000);
		t.start();
		hash += divSum(n, m, a, b);
		t.stop();
	}
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

