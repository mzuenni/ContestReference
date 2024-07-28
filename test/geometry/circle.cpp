#include "../util.h"
constexpr double EPS = 1e-6;
#define ll double
double gcd(double x, double /**/) {return x;} //hacky
#include <geometry/formulas.cpp>
#undef ll
#include <geometry/circle.cpp>

// Entfernung von Punkt p zur Geraden durch a-b. 2d und 3d
double distToLine(pt a, pt b, pt p) {
	return abs(cross(p - a, b - a)) / abs(b - a);
}

pt randomIntegerPT(ll range) {
	return pt(Random::integer<ll>(-range, range), Random::integer<ll>(-range, range));
}

ll sq(ll x) {
	return x*x;
}

int expectedCount(ll x1, ll y1, ll r1, ll x2, ll y2, ll r2) {
	if (x1 == x2 && y1 == y2){
		return r1 == r2 ? -1 : 0;
	} else {
		ll d = sq(x1 - x2) + sq(y1 - y2);

		if (d > sq(r1 + r2) || d < sq(r1 - r2)) {
			return 0;
		} else if (d == sq(r1 + r2) || d == sq(r1 - r2)) {
			return 1;
		} else{
			return 2;
		}
	}
}

void test_circleIntersection(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 1'000'000; tries++) {
		auto c1 = randomIntegerPT(range);
		auto c2 = c1;
		while (c1 == c2) c2 = randomIntegerPT(range);
		double r1 = Random::integer<ll>(1, range);
		double r2 = Random::integer<ll>(1, range);

		auto got = circleIntersection(c1, r1, c2, r2);

		if (sz(got) != expectedCount(real(c1), imag(c1), r1, real(c2), imag(c2), r2)) cerr << "error: wrong count" << FAIL;

		for (int i = 0; i < sz(got); i++) {
			for (int j = 0; j < i; j++) {
				if (abs(got[i] - got[j]) < 1e-6) cerr << "error: identical" << FAIL;
			}
		}

		for (auto p : got) {
			if (float_error(abs(c1 - p), r1) > 1e-6) cerr << "error: 1" << FAIL;
			if (float_error(abs(c2 - p), r2) > 1e-6) cerr << "error: 2" << FAIL;
		}
		queries += sz(got);
	}
	cerr << "tested circleIntersection: " << queries << endl;
}

void test_circleRayIntersection(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 1'000'000; tries++) {
		auto c = randomIntegerPT(range);
		double r = Random::integer<ll>(1, range);

		pt orig = randomIntegerPT(range);
		pt dir = 0;
		while (abs(dir) < 0.5) dir = randomIntegerPT(range);

		auto got = circleRayIntersection(c, r, orig, dir);

		double dist = distToLine(orig, orig + dir, c);
		int lineIntersections = 0;
		if (dist <= r) lineIntersections = 2;
		if (abs(dist - r) < 1e-9) lineIntersections = 1;

		int expected = 0;
		if (abs(orig - c) < r) expected = 1; //starts inside
		if (abs(orig - c) > r) { //starts outside
			if (dot(dir, c - orig) >= 0) expected = lineIntersections;
			else expected = 0;
		}
		if (abs(abs(orig - c) - r) < 1e-9) { //starts on circle
			if (dot(dir, c - orig) >= 0) expected = lineIntersections;
			else expected = 1;
		}

		if (sz(got) != expected) cerr << "error: wrong count" << FAIL;

		for (int i = 0; i < sz(got); i++) {
			for (int j = 0; j < i; j++) {
				if (abs(got[i] - got[j]) < 1e-6) cerr << "error: identical" << FAIL;
			}
		}

		for (auto p : got) {
			if (float_error(abs(c - p), r) > 1e-6) cerr << "error: 1" << FAIL;
			if (distToLine(orig, orig + dir, p) > 1e-6) cerr << "error: 2" << FAIL;
		}
		queries += sz(got);
	}
	cerr << "tested circleIntersection: " << queries << endl;
}

int main() {
	test_circleIntersection(10);
	test_circleIntersection(100);
	test_circleRayIntersection(10);
	test_circleRayIntersection(100);
}
