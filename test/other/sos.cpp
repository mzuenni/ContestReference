#include "../util.h"

vector<ll> sos(const vector<ll>& in) {
	#include <other/sos.cpp>
	return res;
}

vector<ll> naive(const vector<ll>& in) {
	vector<ll> res(sz(in));
	for (ll i = 0; i < sz(in); i++) {
		for (ll j = 0; j <= i; j++) {
			if ((i | j) == i) {
				res[i] += in[j];
			}
		}
	}
	return res;
}

void stress_test() {
	ll tests = 0;
	for (ll i = 0; i < 1000; i++) {
		int n = Random::integer<int>(1, 100);
		auto in = Random::integers<ll>(n, -1000, 1000);
		auto got = sos(in);
		auto expected = naive(in);
		if (got != expected) cerr << "error: " << i << FAIL;
		tests += n;
	}
	cerr << "tested random queries: " << tests << endl;
}

constexpr int N = 10'000'000;
void performance_test() {
	timer t;
	auto in = Random::integers<ll>(N, -1000, 1000);
	t.start();
	auto res = sos(in);
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

