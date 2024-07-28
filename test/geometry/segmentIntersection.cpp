#include "../util.h"
constexpr ll EPS = 0;
#define double ll
#define polar polar<ll>
#include <geometry/formulas.cpp>
#undef polar
#undef double

// Liegt p auf der Strecke a-b?
bool pointOnLineSegment(pt a, pt b, pt p) {
	if (cross(a, b, p) != 0) return false;
	double dist = norm(a - b);
	return norm(a - p) <= dist && norm(b - p) <= dist;
}

// Test auf Streckenschnitt zwischen a-b und c-d.
bool lineSegmentIntersection(pt a, pt b, pt c, pt d) {
	if (ccw(a, b, c) == 0 && ccw(a, b, d) == 0)
			return pointOnLineSegment(a,b,c) ||
			       pointOnLineSegment(a,b,d) ||
			       pointOnLineSegment(c,d,a) ||
			       pointOnLineSegment(c,d,b);
	return ccw(a, b, c) * ccw(a, b, d) <= 0 &&
	       ccw(c, d, a) * ccw(c, d, b) <= 0;
}

#include <geometry/segmentIntersection.cpp>

vector<seg> randomSegs(int n, ll range) {
	auto ps = Random::points<ll>(n, -range, range);
	vector<seg> segs(n);
	for (int i = 0; i < n; i++) {
		pt b;
		do {
			b = Random::point<ll>(-pow(range, 0.8), pow(range, 0.8));
		} while(norm(b) == 0);
		segs[i] = {ps[i], ps[i] + b, i};
	}
	return segs;
}

bool naive(vector<seg>& segs) {
	for (ll i = 0; i < sz(segs); i++) {
		for (ll j = 0; j < i; j++) {
			if (lineSegmentIntersection(segs[i].a, segs[i].b, segs[j].a, segs[j].b)) return true;
		}
	}
	return false;
}

void stress_test(ll range) {
	ll queries = 0;
	ll intersection = 0;
	ll notIntersection = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(2, 100);
		auto segs = randomSegs(n, range);
		auto [a, b] = intersect(segs);
		bool got = a >= 0;
		if (got != (b >= 0)) cerr << "error: invalid ans" << FAIL;
		auto expected = naive(segs);
		if (got != expected) cerr << "error: intersection not found" << FAIL;
		if (got && !lineSegmentIntersection(segs[a].a, segs[a].b, segs[b].a, segs[b].b)) cerr << "error: no intersection" << FAIL;
		queries += n;
		intersection += got;
		notIntersection += !got;
	}
	cerr << "tested random queries: " << queries << "(" << intersection << ":" << notIntersection << ")" << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	auto segs = randomSegs(N, 1'000'000'000);

	t.start();
	hash_t hash = intersect(segs).first;
	t.stop();

	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test(100);
	stress_test(1'000'000'000);
	performance_test();
}
