#include "../util.h"
constexpr ll EPS = 0;
#define double ll
#define polar polar<ll>
#include <geometry/formulas.cpp>
#undef polar
#undef double
#include <geometry/convexHull.cpp>

//strict convex hull
ll isConvexHull(const vector<pt>& ps, const vector<pt>& hull) {
	ll n = sz(hull) - 1;
	if (n == 0) {
		for (pt p : ps) if (p != hull[0]) return 1;
		return 0;
	} else {
		if (hull[0] != hull[n]) return 2;
		//hull has no duplicates
		for (ll i = 0; i < n; i++) {
			for (ll j = 0; j < i; j++) {
				if (hull[i] == hull[j]) return 3;
			}
		}
		//hull is subset
		for (pt p : hull) {
			bool isP = false;
			for (pt c : ps) isP |= c == p;
			if (!isP) return 4;
		}
		//hull contains all points
		for (pt p : hull) {
			ll mi = 1;
			for (ll i = 0; i < n; i++) {
				mi = min(mi, cross(hull[i], hull[i + 1], p));
			}
			if (mi < 0) return 5; //outside
			if (mi > 0) continue;
			bool isCorner = 4;
			for (pt c : hull) isCorner |= c == p;
			if (!isCorner) return 6;
		}
		// hull is convex
		if (n <= 2) return 0;
		for (ll i = 0; i < n; i++) {
			if (cross(hull[i], hull[i + 1], hull[(i + 2) % n]) <= 0) return 7;
		}
		return 0;
	}
}

void stress_test(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 100);
		auto ps = Random::points<ll>(n, -range, range);
		auto got = convexHull(ps);
		if (isConvexHull(ps, got) > 0) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 2'000'000;
void performance_test() {
	timer t;
	auto ps = Random::points<ll>(N, -1'000'000'000, 1'000'000'000);
	t.start();
	auto a = convexHull(ps);
	t.stop();
	hash_t hash = sz(a);
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test(100);
	stress_test(1'000'000'000);
	performance_test();
}
