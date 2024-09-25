#include "../util.h"
constexpr ll EPS = 0;
constexpr double INF = LD::INF;
#define double ll
#define polar polar<ll>
#include <geometry/formulas.cpp>
#undef polar
#undef double
double abs(pt p) {
	return hypot(real(p), imag(p));
}
// Liegt p auf der Strecke a-b?
bool pointOnSegment(pt a, pt b, pt p) {
	if (cross(a, b, p) != 0) return false;
	auto dist = norm(a - b);
	return norm(a - p) <= dist && norm(b - p) <= dist;
}
// Entfernung von Punkt p zur Strecke a-b.
double distToSegment(pt a, pt b, pt p) {
	if (a == b) return abs(p - a);
	if (dot(p - a, b - a) <= 0) return abs(p - a);
	if (dot(p - b, b - a) >= 0) return abs(p - b);
	return abs(cross(p - a, b - a)) / abs(b - a);
}
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <geometry/polygon.cpp>
#include "../geometry.h"

void test_area(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer(3, 30);
		auto ps = Random::polygon(n, range);
		ps.push_back(ps[0]);

		ll expected = 0;
		for (int i = 0; i < n; i++) {
			expected += cross(0, ps[i], ps[i+1]);
		}
		double got = area(ps) * 2;
		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "tested area: " << queries << endl;
}

bool ptLess(pt a, pt b) {
	if (real(a) != real(b)) return real(a) < real(b);
	return imag(a) < imag(b);
}

void test_windingNumber(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer(3, 8);
		auto ps = Random::polygon(n, range);
		ps.push_back(ps[0]);

		for (int i = 0; i < 100; i++) {
			auto p = Random::point<ll>(-range, range);

			ll expected = 0;
			bool onBorder = false;
			for (int j = 0; j < n; j++) {
				int cur = details::lineSegmentIntersection(p, p + pt(1, 2'000'000'007), ps[j], ps[j+1]);
				if (ptLess(ps[j], ps[j+1])) expected -= cur;
				else expected += cur;
				onBorder |= pointOnSegment(ps[j], ps[j+1], p);
			}
			if (onBorder) continue;
			if (area(ps) < 0) expected = -expected;

			bool got = windingNumber(p, ps);

			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		}
		queries += n;
	}
	cerr << "tested windingNumber: " << queries << endl;
}

void test_inside(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer(3, 30);
		auto ps = Random::polygon(n, range);
		ps.push_back(ps[0]);

		for (int i = 0; i < 100; i++) {
			auto p = Random::point<ll>(-range, range);

			ll count = 0;
			bool onBorder = false;
			for (int j = 0; j < n; j++) {
				count += details::lineSegmentIntersection(p, p + pt(1, 2'000'000'007), ps[j], ps[j+1]);
				onBorder |= pointOnSegment(ps[j], ps[j+1], p);
			}
			bool expected = (count % 2) && !onBorder;
			bool got = inside(p, ps);

			if (got != expected) cerr << "error" << FAIL;
		}
		queries += n;
	}
	cerr << "tested inside: " << queries << endl;
}

void test_insideConvex(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer(3, 30);
		auto ps = Random::convex(n, range);

		for (int i = 0; i < 100; i++) {
			auto p = Random::point<ll>(-range, range);

			bool expected = true;
			for (int j = 0; j < n; j++) expected &= cross(p, ps[j], ps[(j+1) % n]) > 0;

			bool got = insideConvex(p, ps);

			if (got != expected) {
				for (pt pp : ps) cerr << pp << " ";
				cerr << endl;
				cerr << p << endl;
			}

			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		}
		queries += n;
	}
	cerr << "tested insideConvex: " << queries << endl;
}

// convex hull without duplicates, h[0] != h.back()
// apply comments if border counts as inside
bool insideOrOnConvex(pt p, const vector<pt>& hull) {
	int l = 0, r = sz(hull) - 1;
	if (cross(hull[0], hull[r], p) > 0) return false;
	while (l + 1 < r) {
		int m = (l + r) / 2;
		if (cross(hull[0], hull[m], p) >= 0) l = m;
		else r = m;
	}
	return cross(hull[l], hull[r], p) >= 0;
}

void test_minkowski(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer(3, 30);
		auto A = Random::convex(n, range);
		int m = Random::integer(3, 30);
		auto B = Random::convex(n, range);

		auto got = minkowski(A, B);
		bool convex = true;
		for (int i = 0; i < sz(got); i++) convex &= cross(got[i], got[(i+1) % sz(got)], got[(i+2) % sz(got)]) >= 0;
		if (!convex) cerr << "error: not convex" << FAIL;

		for (pt a : A) {
			for (pt b : B) {
				if (!insideOrOnConvex(a + b, got)) cerr << "error: not sum" << FAIL;
			}
		}
		queries += n + m;
	}
	cerr << "tested minkowski: " << queries << endl;
}

double naive_dist(const vector<pt>& ps, const vector<pt>& qs) {
	//check if intersect
	double res = LD::INF;
	bool intersect = true;
	for (int i = 0; i < sz(qs); i++) {
		bool sep = true;
		for (pt p : ps) {
			res = min(res, distToSegment(qs[i], qs[(i+1) % sz(qs)], p));
			sep &= cross(qs[i], qs[(i+1) % sz(qs)], p) <= 0;
		}
		if (sep) intersect = false;
	}
	for (int i = 0; i < sz(ps); i++) {
		bool sep = true;
		for (pt q : qs) {
			res = min(res, distToSegment(ps[i], ps[(i+1) % sz(ps)], q));
			sep &= cross(ps[i], ps[(i+1) % sz(ps)], q) <= 0;
		}
		if (sep) intersect = false;
	}
	if (intersect) return 0;
	return res;
}

void test_dist(ll range) {
	int queries = 0;
	int pos = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer(3, 10);
		auto A = Random::convex(n, range / 3);
		int m = Random::integer(3, 10);
		auto B = Random::convex(n, range / 3);

		pt offset = Random::point<ll>(range / 3, 2 * range / 3);
		for (pt& p : B) p += offset;

		auto got = dist(A, B);
		auto expected = naive_dist(A, B);

		if (float_error(got, expected) > 1e-6) cerr << "got: " << got << ", expected: " << expected << FAIL;
		if (got > 0) pos++;

		queries += n + m;
	}
	cerr << "tested dist: " << queries << " (" << pos << ")" << endl;
}

void test_extremal(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer(3, 30);
		auto ps = Random::convex(n, range);
		ps.push_back(ps[0]);

		for (int i = 0; i < 100; i++) {
			auto dir = Random::point<ll>(-range, range);
			int tmp = extremal(ps, dir);
			if (tmp < 0 || tmp >= n) cerr << "error: out of range" << FAIL;

			auto got = ps[tmp];
			bool extremal = true;
			for (pt p : ps) extremal &= dot(dir, p) <= dot(dir, got);

			if (!extremal) cerr << "error: not extremal" << FAIL;
			queries += n;
		}
	}
	cerr << "tested extremal: " << queries << endl;
}

void test_intersect(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer(3, 10);
		auto ps = Random::convex(n, range);
		ps.push_back(ps[0]);

		for (int i = 0; i < 100; i++) {
			pt a = Random::point<ll>(-range, range);
			pt b = a;
			while (b == a) b = Random::point<ll>(-range, range);

			auto got = intersectLine(ps, a, b);

			vector<int> expected;
			for (int j = 0; j < n; j++) {
				if (cross(ps[j], a, b) > 0 && cross(ps[j+1], a, b) < 0) expected.push_back(j);
				if (cross(ps[j], a, b) < 0 && cross(ps[j+1], a, b) > 0) expected.push_back(j);
				if (cross(ps[j], a, b) == 0) {
					if (cross(ps[j+1], a, b) != 0 ||
						cross(ps[(j+n-1) % n], a, b) != 0) {
						expected.push_back(j);
					}
				}
			}
			if (sz(expected) > 1 && expected[0] == expected[1]) expected.pop_back();

			sort(all(got));
			sort(all(expected));

			if (got != expected) cerr << "error" << FAIL;

			queries += n;
		}
	}
	cerr << "tested intersect: " << queries << endl;
}

int main() {
	test_area(100);
	test_area(1'000'000'000);
	test_windingNumber(100);
	test_windingNumber(1'000'000'000);
	test_inside(100);
	test_inside(1'000'000'000);
	test_insideConvex(100);
	test_insideConvex(1'000'000'000);
	test_minkowski(100);
	test_minkowski(500'000'000);
	test_dist(100);
	test_dist(1'000'000'000);
	test_extremal(100);
	test_extremal(1'000'000'000);
	test_intersect(100);
	test_intersect(1'000'000'000);
}
