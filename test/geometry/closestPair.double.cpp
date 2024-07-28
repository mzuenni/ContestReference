#include "../util.h"
constexpr double EPS = 1e-9;
#define ll double
double gcd(double x, double /**/) {return x;} //hacky
#include <geometry/formulas.cpp>
constexpr ll INF = LL::INF;
#include <geometry/closestPair.cpp>
#undef ll

//strict convex hull
double naive(const vector<pt>& ps) {
	double opt = LL::INF;
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
		auto ps = Random::points<double>(n, -range, range);
		auto got = shortestDist(ps);
		auto expected = naive(ps);
		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	hash_t hash = 0;
	double maxTime = 0;

	vector<pt> ps;
	for (int i = 0; i*i <= N; i++) {
		for (int j = 0; j*j <= N; j++) {
			ps.emplace_back(i, j);
		}
	}
	t.start();
	hash = shortestDist(ps);
	t.stop();
	maxTime = max(maxTime, t.time);

	ps = Random::points<double>(N, -1'000'000'000, 1'000'000'000);
	t.reset();
	t.start();
	hash += shortestDist(ps);
	t.stop();
	maxTime = max(maxTime, t.time);

	if (maxTime > 500) cerr << "too slow: " << maxTime << FAIL;
	cerr << "tested performance: " << maxTime << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test(100);
	stress_test(1'000'000'000);
	performance_test();
}
