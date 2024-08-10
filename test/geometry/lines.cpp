#include "../util.h"
constexpr double EPS = 1e-6;
#define ll double
double gcd(double x, double /**/) {return x;} //hacky
#include <geometry/formulas.cpp>
#undef ll
#include <geometry/linesAndSegments.cpp>
#include <geometry/lines.cpp>

#include "../geometry.h"

void stress_pointsToLine(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);

		line gotA(a, b);
		if (real(a) != real(b)) {
			gotA.a /= gotA.b;
			gotA.c /= gotA.b;
			gotA.b /= gotA.b;
		} else {
			gotA.c /= gotA.a;
			gotA.a /= gotA.a;
		}
		line gotB = pointsToLine(a, b);

		if (!same(gotA, gotB)) cerr << "error" << FAIL;
		queries++;
	}
	cerr << "tested pointsToLine: " << queries << endl;
}

void stress_same(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		auto [c, d] = Random::line(range);

		line lAB = pointsToLine(a, b);
		line lCD = pointsToLine(c, d);

		auto got = same(lAB, lCD);
		auto expected = pointOnLine(a, b, c) && pointOnLine(a, b, d);

		if (got != expected) cerr << "error" << FAIL;
		queries++;
	}
	cerr << "tested same: " << queries << endl;
}

void stress_parallel(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		auto [c, d] = Random::line(range);

		line lAB = pointsToLine(a, b);
		line lCD = pointsToLine(c, d);

		auto got = parallel(lAB, lCD);
		auto expected = cross(b-a, d-c) == 0;

		if (got != expected) cerr << "error" << FAIL;
		queries++;
	}
	cerr << "tested parallel: " << queries << endl;
}

void stress_intersect(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		auto [c, d] = Random::line(range);

		line lAB = pointsToLine(a, b);
		line lCD = pointsToLine(c, d);

		if (same(lAB, lCD)) continue;

		pt gotPT;
		auto got = intersect(lAB, lCD, gotPT);
		auto expected = lineIntersection(a, b, c, d);

		if (got != expected) cerr << "error: 1" << FAIL;
		if (got) {
			pt expectedPt = lineIntersection2(a, b, c, d);
			if (float_error(real(gotPT), real(expectedPt)) > 1e-6) cerr << "error: 2" << FAIL;
			if (float_error(imag(gotPT), imag(expectedPt)) > 1e-6) cerr << "error: 2" << FAIL;
		}
		queries++;
	}
	cerr << "tested intersect: " << queries << endl;
}

int main() {
	stress_pointsToLine(100);
	stress_pointsToLine(100'000);
	stress_same(10);
	stress_same(100);
	stress_same(1'000'000'000);//no precision issue since this will alwas be false...
	stress_parallel(10);
	stress_parallel(100);
	stress_parallel(1'000'000'000);
	stress_intersect(100);
	stress_intersect(1'000'000'000);
}
