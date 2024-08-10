#include "../util.h"
constexpr double EPS = 1e-6;
struct pt3 {
	double x, y, z;
	pt3 operator-(const pt3 o) const {
		return {x-o.x, y-o.y, z-o.z};
	}
	pt3 operator+(const pt3 o) const {
		return {x+o.x, y+o.y, z+o.z};
	}

	pt3 operator*(double m) const {
		return {x*m, y*m, z*m};
	}

	pt3 operator/(double d) const {
		return {x/d, y/d, z/d};
	}

	friend ostream& operator<<(ostream& os, pt3 p) {
		return os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
	}
};

pt3 cross(pt3 a, pt3 b);
double abs(pt3 p);
double distToLine(pt3 a, pt3 b, pt3 p) {
	return abs(cross(p - a, b - a)) / abs(b - a);
}

#include <geometry/formulas3d.cpp>

namespace Random {
	pt3 point3d(ll l, ll r) {
		return {
			(double)integer<ll>(l, r),
			(double)integer<ll>(l, r),
			(double)integer<ll>(l, r),
		};
	}

	template<size_t C>
	std::array<pt3, C> distinct(ll l, ll r) {
		std::array<pt3, C> res = {};
		for (size_t i = 0; i < C; i++) {
			bool unqiue;
			do {
				res[i] = point3d(l, r);
				unqiue = true;
				for (size_t j = 0; j < i; j++) {
					unqiue &= res[j].x != res[i].x ||
					          res[j].y != res[i].y ||
					          res[j].z != res[i].z;
				}
			} while (!unqiue);
		}
		return res;
	}
}

void test_dot(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto p = Random::point3d(-range, range);
		auto q = Random::point3d(-range, range);

		auto expected = p.x*q.x + p.y*q.y + p.z*q.z;
		auto got = dot(p, q);

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested dot: " << queries << endl;
}

void test_cross(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto p = Random::point3d(-range, range);
		auto q = Random::point3d(-range, range);

		auto expected = pt3{p.y*q.z - p.z*q.y,
		                    p.z*q.x - p.x*q.z,
		                    p.x*q.y - p.y*q.x};
		auto got = cross(p, q);

		if (got.x != expected.x) cerr << "error: x" << FAIL;
		if (got.y != expected.y) cerr << "error: y" << FAIL;
		if (got.z != expected.z) cerr << "error: z" << FAIL;
		queries++;
	}
	cerr << "tested cross: " << queries << endl;
}

void test_abs(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto p = Random::point3d(-range, range);

		auto expected = sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
		auto got = abs(p);

		if (abs(got - expected) > 1e-6) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested abs: " << queries << endl;
}

void test_mixed(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto a = Random::point3d(-range, range);
		auto b = Random::point3d(-range, range);
		auto c = Random::point3d(-range, range);

		auto expected = dot(cross(a, b), c);
		auto got = mixed(a, b, c);

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested mixed: " << queries << endl;
}

void test_ccw(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto a = Random::point3d(-range, range);
		auto b = Random::point3d(-range, range);
		auto c = Random::point3d(-range, range);
		auto d = Random::point3d(-range, range);

		ll expected = mixed(b - a, c - a, d - a);
		if (expected < 0) expected = -1;
		if (expected > 0) expected = 1;
		auto got = ccw(a, b, c, d);

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested ccw: " << queries << endl;
}

void test_distToPlane(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [p, q] = Random::distinct<2>(-range, range);
		auto [a, b, c] = Random::distinct<3>(-range, range);

		auto norm = cross(a - c, b - c);
		norm = norm / abs(norm);

		auto gotA = distToPlane(a, b, c, p);
		auto gotB = distToPlane(a, b, c, q);
		auto got = ccw(a, b, c, p) * ccw(a, b, c, q) < 0 ? gotA + gotB : abs(gotA - gotB);

		auto expected = abs(dot(norm, p - q));

		if (abs(got - expected) > 1e-6) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested distToPlane: " << queries << endl;
}

void stress_pointOnPlane(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto p = Random::point3d(-range, range);
		auto [a, b, c] = Random::distinct<3>(-range, range);

		bool expected = ccw(a, b, c, p) == 0;
		bool got = pointOnPlane(a, b, c, p);

		if (got != expected) cerr << "error" << FAIL;
		queries++;
	}
	cerr << "tested pointOnPlane: " << queries << endl;
}

void test_linePlaneIntersection(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [p, q] = Random::distinct<2>(-range, range);
		auto [a, b, c] = Random::distinct<3>(-range, range);

		if (abs(dot(p - q, cross(a-c, b-c))) < 1e-6) continue; 

		auto got = linePlaneIntersection(p, q, a, b, c);

		if (distToLine(p, q, got) > 1e-6) cerr << "error: 1" << FAIL;
		if (distToPlane(a, b, c, got) > 1e-6) cerr << "error: 2" << FAIL;
		queries++;
	}
	cerr << "tested linePlaneIntersection: " << queries << endl;
}

void test_lineLineDist(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto [p, q] = Random::distinct<2>(-range, range);
		auto [a, b] = Random::distinct<2>(-range, range);

		double expected = 0;
		if (ccw(a, b, p, q) != 0) {
			pt3 c = a + p - q;
			expected = distToPlane(a, b, c, p);
		}
		auto got = lineLineDist(p, q, a, b);
		
		if (abs(got - expected) > 1e-6) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested lineLineDist: " << queries << endl;
}

int main() {
	test_dot(100);
	test_dot(1'000'000);
	test_cross(100);
	test_cross(1'000'000);
	test_abs(100);
	test_abs(1'000'000);
	test_mixed(100);
	test_mixed(1'000'000);
	test_ccw(100);
	test_ccw(1'000'000);

	test_distToPlane(100);
	test_distToPlane(1'000'000);
	stress_pointOnPlane(100);
	stress_pointOnPlane(1'000'000);
	test_linePlaneIntersection(100);
	test_linePlaneIntersection(1'000);//can be far away
	test_lineLineDist(100);
	test_lineLineDist(1'000'000);
}
