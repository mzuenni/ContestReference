#include "../util.h"
constexpr ll EPS = 0;
#define double ll
#define polar polar<ll>
#include <geometry/formulas.cpp>
#undef polar
#undef double

void test_dot(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto p = Random::point<ll>(-range, range);
		auto q = Random::point<ll>(-range, range);

		ll expected = real(p) * real(q) + imag(p) * imag(q);
		ll got = dot(p, q);

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested dot: " << queries << endl;
}

void test_norm(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto p = Random::point<ll>(-range, range);

		ll expected = real(p) * real(p) + imag(p) * imag(p);
		ll got = norm(p);

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested norm: " << queries << endl;
}

void test_cross(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto p = Random::point<ll>(-range, range);
		auto q = Random::point<ll>(-range, range);

		ll expected = real(p) * imag(q) - imag(p) * real(q);
		ll got = cross(p, q);

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested cross1: " << queries << endl;

	queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto a = Random::point<ll>(-range, range);
		auto b = Random::point<ll>(-range, range);
		auto c = Random::point<ll>(-range, range);

		ll expected = cross(b - a, c - a);
		ll got = cross(a, b, c);

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested cross2: " << queries << endl;
}

void test_ccw(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto a = Random::point<ll>(-range, range);
		auto b = Random::point<ll>(-range, range);
		auto c = Random::point<ll>(-range, range);

		ll expected = cross(a, b, c);
		if (expected < 0) expected = -1;
		if (expected > 0) expected = 1;
		ll got = ccw(a, b, c);

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested ccw: " << queries << endl;
}

void test_isCoplanar(ll range) {(void) range;}// cant check this...

void test_uniqueAngle(ll range) {
	auto lessPt = [](pt a, pt b){
		if (real(a) != real(b)) return real(a) < real(b);
		return imag(a) < imag(b);
	};
	map<pt, pt, decltype(lessPt)> seen(lessPt);

	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		pt expected = Random::point<ll>(-sqrt(range), sqrt(range));
		ll g = abs(gcd(real(expected), imag(expected)));
		if (g == 0) continue;
		expected /= g;

		pt rot = Random::point<ll>(-sqrt(range), sqrt(range));
		if (norm(rot) == 0) continue;

		pt got = uniqueAngle(expected * rot, pt(Random::integer<ll>(1, sqrt(range)), 0) * rot);
		auto it = seen.emplace(got, expected).first;

		if (it->second != expected) cerr << "error: inconsistent" << FAIL;
		queries++;
	}
	cerr << "tested uniqueAngle: " << queries << " (" << sz(seen) << ")" << endl;
}

int main() {
	test_dot(100);
	test_dot(1'000'000'000);
	test_norm(100);
	test_norm(1'000'000'000);
	test_cross(100);
	test_cross(1'000'000'000);
	test_ccw(100);
	test_ccw(1'000'000'000);
	test_isCoplanar(100);
	test_isCoplanar(1'000'000'000);
	test_uniqueAngle(100);
	test_uniqueAngle(10'000);
	test_uniqueAngle(1'000'000'000);
}
