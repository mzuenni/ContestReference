#include "../util.h"
#include <datastructures/pbds.cpp>
#include <math/cycleDetection.cpp>

pair<ll, ll> naive(ll x0, function<ll(ll)> f) {
	map<ll, ll> seen;
	ll d = 0;
	while (seen.find(x0) == seen.end()) {
		seen[x0] = d;
		d++;
		x0 = f(x0);
	}
	return {seen[x0], d - seen[x0]};
}

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 1000'000; i++) {
		int m = Random::integer<int>(1, 100);
		int c = Random::integer<int>(0, m);
		auto f = [&](ll x){return (x*x + c) % m;};
		int x0 = Random::integer<int>(0, m);
		auto got = cycleDetection(x0, f);
		auto expected = naive(x0, f);
		if (got != expected) cerr << "error: " << got.first << " " << got.second << " " << expected.first << " " << expected.second << FAIL;
		queries += got.second;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr ll M = 18'086'183;
void performance_test() {
	timer t;
	auto f = [&](ll x){return (1337*x + 42) % M;};
	t.start();
	auto [a, b] = cycleDetection(42, f);
	t.stop();
	hash_t hash = a + b;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

