#include "../util.h"
#include <other/josephus2.cpp>

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
	for (ll i = 1; i < 2'000; i++) {
		auto got = rotateLeft(i);
		auto expected = naive<1>(i, 2);
		if (got != expected) cerr << "error: " << i << FAIL;
		tests++;
	}
	cerr << "tested queries: " << tests << endl;
}

constexpr int N = 1'000'000'000;
void performance_test() {
	timer t;
	hash_t hash = 0;
	t.start();
	for (ll i = 0; i < N; i++) {
		hash += rotateLeft(1'000'000'000'000'000'000ll + i);
	}
	t.stop();
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

