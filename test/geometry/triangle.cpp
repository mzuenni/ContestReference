#include "../util.h"
constexpr double EPS = 1e-6;
#define ll double
double gcd(double x, double /**/) {return x;} //hacky
#include <geometry/formulas.cpp>
#undef ll
ll sgn(double x) {
	return (x > EPS) - (x < -EPS);
}
#include <geometry/triangle.cpp>

// Entfernung von Punkt p zur Geraden durch a-b. 2d und 3d
double distToLine(pt a, pt b, pt p) {
	return abs(cross(p - a, b - a)) / abs(b - a);
}

pt randomIntegerPT(ll range) {
	return pt(Random::integer<ll>(-range, range), Random::integer<ll>(-range, range));
}

array<pt, 3> randomTriangle(ll range) {
	pt a = randomIntegerPT(range);
	pt b = a;
	while (b == a) b = randomIntegerPT(range);
	pt c = a;
	while (ccw(a, b, c) == 0) c = randomIntegerPT(range);
	return {a, b, c};
}

void test_centroid(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 1'000'000; tries++) {
		auto [a, b, c] = randomTriangle(range);

		pt center = centroid(a, b, c);

		if (distToLine(2.0*a, c+b, 2.0*center) > 1e-6) cerr << "error: 1" << FAIL;
		if (distToLine(2.0*b, c+a, 2.0*center) > 1e-6) cerr << "error: 2" << FAIL;
		if (distToLine(2.0*c, a+b, 2.0*center) > 1e-6) cerr << "error: 3" << FAIL;
		queries++;
	}
	cerr << "tested centroid: " << queries << endl;
}

void test_area(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 1'000'000; tries++) {
		auto [a, b, c] = randomTriangle(range);

		auto gotA = area(a, b, c);
		auto gotB = area(abs(a-b), abs(b-c), abs(c-a));
		if (float_error(gotA, gotB) > 1e-6) cerr << "error: 1" << FAIL;
		if (float_error(gotB, gotA) > 1e-6) cerr << "error: 2" << FAIL;
		queries++;
	}
	cerr << "tested area: " << queries << endl;
}

void test_inCenter(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 1'000'000; tries++) {
		auto [a, b, c] = randomTriangle(range);

		pt center = inCenter(a, b, c);

		double da = distToLine(a, b, center);
		double db = distToLine(b, c, center);
		double dc = distToLine(c, a, center);

		double avg = (da + db + dc) / 3.0;

		if (float_error(da, avg) > 1e-6) cerr << "error: 1" << FAIL;
		if (float_error(db, avg) > 1e-6) cerr << "error: 2" << FAIL;
		if (float_error(dc, avg) > 1e-6) cerr << "error: 3" << FAIL;
		queries++;
	}
	cerr << "tested inCenter: " << queries << endl;
}

void test_circumCenter(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 1'000'000; tries++) {
		auto [a, b, c] = randomTriangle(range);

		pt center = circumCenter(a, b, c);

		double da = abs(center - a);
		double db = abs(center - b);
		double dc = abs(center - c);

		double avg = (da + db + dc) / 3.0;

		if (float_error(da, avg) > 1e-6) cerr << "error: 1" << FAIL;
		if (float_error(db, avg) > 1e-6) cerr << "error: 2" << FAIL;
		if (float_error(dc, avg) > 1e-6) cerr << "error: 3" << FAIL;
		queries++;
	}
	cerr << "tested circumCenter: " << queries << endl;
}

void test_insideOutCenter(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 1'000'000; tries++) {
		auto [a, b, c] = randomTriangle(range);
		pt p = randomIntegerPT(range);

		pt center = circumCenter(a, b, c);

		double da = abs(center - a);
		double db = abs(center - b);
		double dc = abs(center - c);
		double dp = abs(center - p);

		double avg = (da + db + dc) / 3.0;

		int expected = dp < avg ? 1 : -1;
		if (float_error(dp, avg) < 1e-9) expected = 0;

		if (insideOutCenter(a, b, c, p) != expected) cerr << "error" << FAIL;

		queries++;
	}
	cerr << "tested insideOutCenter: " << queries << endl;
}

void test_similar(ll range) {
	int queries = 0;
	for (int tries = 0; tries < 1'000'000; tries++) {
		auto [a, b, c] = randomTriangle(range);
		pt rot = randomIntegerPT(range);
		pt add = randomIntegerPT(range);

		pt d = rot * a + add;
		pt e = rot * b + add;
		pt f = rot * c + add;

		if (!similar(a, b, c, d, e, f)) cerr << "error" << FAIL;
		queries++;
	}
	cerr << "tested similar: " << queries << endl;
}

int main() {
	test_centroid(10);
	test_centroid(100);
	test_area(10);
	test_area(100);
	test_inCenter(10);
	test_inCenter(100);
	test_circumCenter(10);
	test_circumCenter(100);
	test_insideOutCenter(10);
	test_insideOutCenter(100);
	test_similar(10);
	test_similar(100);
}
