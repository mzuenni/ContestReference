#include "../util.h"
#include <other/josephus2.cpp>
#include <other/josephusK.cpp>

template<ll O>
ll naive(ll n, ll k) {
	vector<ll> state(n);
	iota(all(state), O);
	for (ll i = k-1; state.size() > 1; i = (i + k - 1) % sz(state)) {
		state.erase(state.begin() + i);
	}
	return state[0];
}

void stress_test() {
	ll tests = 0;
	for (ll i = 1; i < 500; i++) {
		for (ll j = 1; j <= i; j++) {
			auto got = josephus(i, j);
			auto expected = naive<0>(i, j);
			if (got != expected) cerr << "error: " << i << FAIL;
			tests++;
		}
	}
	cerr << "tested queries: " << tests << endl;
}

constexpr int N = 10'000'000;
void performance_test() {
	timer t;
	hash_t hash = 0;
	t.start();
	hash += josephus(N, N/2);
	t.stop();
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

