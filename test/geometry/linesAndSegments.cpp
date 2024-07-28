#include "../util.h"
constexpr double EPS = 1e-9;
#define ll double
double gcd(double x, double /**/) {return x;} //hacky
#include <geometry/formulas.cpp>
#undef ll
#include <geometry/linesAndSegments.cpp>

#include "../geometry.h"

void stress_pointOnLine(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		pt p = Random::integerPoint(range);

		bool expected = ccw(a, b, p) == 0;
		bool got = pointOnLine(a, b, p);

		if (got != expected) cerr << "error" << FAIL;
		queries++;
	}
	cerr << "tested pointOnLine: " << queries << endl;
}

void stress_lineIntersection(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		auto [c, d] = Random::line(range);
		if (ccw(a, b, c) == 0 && ccw(a, b, d) == 0) continue;

		bool expected = ccw(0, a-b, c-d) == 0;
		bool got = lineIntersection(a, b, c, d);

		if (got != expected) cerr << "error" << FAIL;
		queries++;
	}
	cerr << "tested lineIntersection: " << queries << endl;
}

void stress_lineIntersection2(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		auto [c, d] = Random::line(range);
		if (ccw(0, a-b, c-d) == 0) continue;

		auto got = lineIntersection2(a, b, c, d);

		if (distToLine(a, b, got) > 1e-6) cerr << "error: 1" << FAIL;
		if (distToLine(a, b, got) > 1e-6) cerr << "error: 2" << FAIL;
		queries++;
	}
	cerr << "tested lineIntersection2: " << queries << endl;
}

void stress_distToLine(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		pt p = Random::integerPoint(range);

		auto got = distToLine(a, b, p);
		auto expected = abs(p - projectToLine(a, b, p));

		if (float_error(got, expected) > 1e-6) cerr << "error" << FAIL;

		queries++;
	}
	cerr << "tested distToLine: " << queries << endl;
}

void stress_projectToLine(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		pt p = Random::integerPoint(range);

		auto got = projectToLine(a, b, p);

		if (distToLine(a, b, got) > 1e-6) cerr << "error: 1" << FAIL;
		if (dot((b-a)/abs(b-a), (got-p)/abs(got-p)) > 1e-6) cerr << "error: 2" << FAIL;

		queries++;
	}
	cerr << "tested projectToLine: " << queries << endl;
}

void stress_sortLine(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		pt dir = 0;
		while (norm(dir) == 0) dir = Random::integerPoint(range);
		int n = Random::integer<int>(1, 30);
		vector<pt> ps = Random::integerPoints(n, range);

		sortLine(dir, ps);

		for (int i = 1; i < n; i++) {
			if (dot(dir, ps[i-1]) > dot(dir, ps[i])) cerr << "error" << FAIL;
		}
		queries+=n;
	}
	cerr << "tested sortLine: " << queries << endl;
}

void stress_pointOnSegment(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		pt p = Random::integerPoint(range);

		bool expected = pointOnLine(a, b, p) && abs(a-p) <= abs(a-b) && abs(b-p) <= abs(a-b);
		bool got = pointOnSegment(a, b, p);

		if (got != expected) cerr << "error" << FAIL;
		queries++;
	}
	cerr << "tested pointOnSegment: " << queries << endl;
}

void stress_distToSegment(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		pt p = Random::integerPoint(range);

		double expected = min(abs(p-a), abs(p-b));
		if (dot(b-a,p-a) >= 0 && dot(a-b,p-b) >= 0) expected = min(expected, distToLine(a, b, p));
		double got = distToSegment(a, b, p);

		if (float_error(got, expected) > 1e-6) cerr << "error" << FAIL;
		queries++;
	}
	cerr << "tested distToSegment: " << queries << endl;
}

void stress_segmentIntersection(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		auto [c, d] = Random::line(range);

		bool expected;
		if (ccw(a, b, c) == 0 && ccw(a, b, d) == 0) {
			expected = pointOnSegment(a,b,c) ||
			           pointOnSegment(a,b,d) ||
			           pointOnSegment(c,d,a) ||
			           pointOnSegment(c,d,b);
		} else {
			expected = ccw(a, b, c) * ccw(a, b, d) <= 0 &&
	       	           ccw(c, d, a) * ccw(c, d, b) <= 0;
		}
		bool got = segmentIntersection(a, b, c, d);

		if (got != expected) cerr << "error" << FAIL;
		queries++;
	}
	cerr << "tested segmentIntersection: " << queries << endl;
}

void stress_segmentIntersection2(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		auto [c, d] = Random::line(range);

		auto got = segmentIntersection2(a, b, c, d);
		auto tmp = segmentIntersection(a, b, c, d);

		if (!got.empty() != tmp) cerr << "error: 1" << FAIL;
		for (pt p : got) {
			if (distToSegment(a, b, p) > 1e-6) cerr << "error: 2" << FAIL;
			if (distToSegment(a, b, p) > 1e-6) cerr << "error: 3" << FAIL;
		}
		if (tmp) {
			double gotDist = abs(got.front() - got.back());
			double expectedDist = 0;
			array<pt, 4> tmp2 = {a, b, c, d};
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < i; j++) {
					if (!pointOnSegment(a, b, tmp2[i])) continue;
					if (!pointOnSegment(c, d, tmp2[i])) continue;
					if (!pointOnSegment(a, b, tmp2[j])) continue;
					if (!pointOnSegment(c, d, tmp2[j])) continue;
					expectedDist = max(expectedDist, abs(tmp2[i] - tmp2[j]));
				}
			}
			if (float_error(gotDist, expectedDist) > 1e-6) cerr << "error: 4" << FAIL;
		}
		queries++;
	}
	cerr << "tested segmentIntersection2: " << queries << endl;
}

void stress_distBetweenSegments(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [a, b] = Random::line(range);
		auto [c, d] = Random::line(range);

		double expected = 0;
		if (!segmentIntersection(a, b, c, d)) {
			expected = min({distToSegment(a, b, c), distToSegment(a, b, d),
			                distToSegment(c, d, a), distToSegment(c, d, b)});
		}
		double got = distBetweenSegments(a, b, c, d);

		if (float_error(got, expected) > 1e-6) cerr << "error" << FAIL;
		queries++;
	}
	cerr << "tested distBetweenSegments: " << queries << endl;
}

int main() {
	stress_pointOnLine(100);
	stress_pointOnLine(10'000);
	stress_pointOnLine(1'000'000'000);
	stress_lineIntersection(100);
	stress_lineIntersection(1'000'000'000);
	stress_lineIntersection2(100);
	stress_lineIntersection2(1'000'000);
	stress_distToLine(100);
	stress_distToLine(1'000'000'000);
	stress_projectToLine(100);
	stress_projectToLine(1'000'000);
	stress_sortLine(100);
	stress_sortLine(1'000'000'000);
	stress_pointOnSegment(100);
	stress_pointOnSegment(1'000'000'000);
	stress_distToSegment(100);
	stress_distToSegment(1'000'000'000);
	stress_segmentIntersection(100);
	stress_segmentIntersection(1'000'000'000);
	stress_segmentIntersection2(100);
	stress_segmentIntersection2(1'000'000'000);
	stress_distBetweenSegments(100);
	stress_distBetweenSegments(1'000'000'000);
}
