#include "../util.h"
constexpr ll EPS = 0;
#define double ll
#define polar polar<ll>
#include <geometry/formulas.cpp>
#undef polar
#undef double
constexpr ll INF = LL::INF;
ll sq(ll x) {return x*x;}
ll isqrt(ll x) {return (ll)sqrtl(x);}
#include <geometry/closestPair.cpp>

//strict convex hull
ll naive(const vector<pt>& ps) {
	ll opt = LL::INF;
	for (ll i = 0; i < sz(ps); i++) {
		for (ll j = 0; j < i; j++) {
			opt = min(opt, norm(ps[i] - ps[j]));
		}
	}
	return opt;
}

void stress_test(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(2, 100);
		auto ps = Random::points<ll>(n, -range, range);
		auto got = shortestDist(ps);
		auto expected = naive(ps);
		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "  tested random queries: " << queries << endl;
}

constexpr int N = 2'000'000;
void performance_test() {
	timer t;
	auto ps = Random::points<ll>(N, -1'000'000'000, 1'000'000'000);
	t.start();
	hash_t hash = shortestDist(ps);
	t.stop();
	if (t.time > 500) cerr << "  too slow: " << t.time << FAIL;
	cerr << "  tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test(100);
	stress_test(1'000'000'000);
	performance_test();
}
