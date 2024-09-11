#include "../util.h"
constexpr ll EPS = 0;
#define double ll
#define polar polar<ll>
#include <geometry/formulas.cpp>
#undef polar
#undef double
#include "../geometry.h"
ll sgn(ll x) {
	return (x > 0) - (x < 0);
}
#include <geometry/hpi.cpp>

using ptd = complex<long double>;
ptd convert(pt x) {return ptd(real(x), imag(x));}
auto cross(ptd a, ptd b) {return imag(conj(a) * b);}
auto cross(ptd p, ptd a, ptd b) {return cross(a - p, b - p);}
ptd lineIntersection2(ptd a, ptd b, ptd c, ptd d) {
	ld x = cross(b - a, d - c);
	ld y = cross(c - a, d - c);
	return a + y/x*(b - a);
}

//check if a is dominated by b and c
bool naiveCheck(array<pt, 2> a, array<pt, 2> b, array<pt, 2> c) {
	//https://cp-algorithms.com/geometry/halfplane-intersection.html
	//intersect b and c
	//check cross of a and intersection
	ptd intersection = lineIntersection2(
		convert(b[0]),
		convert(b[1]),
		convert(c[0]),
		convert(c[1])
	);
	return cross(convert(a[0]), convert(a[1]), intersection) <= -1e-12;
}
//real(a - p)*imag(b - p)-imag(a - p)*real(b - p)

void test_check(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto a = Random::line(range);
		auto b = Random::line(range);
		auto c = b;
		while (
			cross(b[0] - b[1], c[0] - c[1]) == 0
			//||cross(a[0] - a[1], b[0] - b[1], c[0] - c[1]) >= 0
		) c = Random::line(range);
		
		bool got = hp(a[0], a[1]).check(hp(b[0], b[1]), hp(c[0], c[1]));
		bool expected = naiveCheck(a, b, c);

		if (got != expected) {
			cout << tries << endl;
			cout << a[0] << " " << a[1] << endl;
			cout << b[0] << " " << b[1] << endl;
			cout << c[0] << " " << c[1] << endl;
			cout << boolalpha << got << " " << expected << endl;
			cerr << "error" << FAIL;
		}
		queries++;
	}
	cerr << "tested random queries: " << queries << endl;
}

/*void stress_test(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto centre = Random::point<ll>(n, -range / 2, range / 2);

	}
	cerr << "tested random queries: " << queries << endl;
}*/

/*constexpr int N = 1'000'000;
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

	ps = Random::points<ll>(N, -1'000'000'000, 1'000'000'000);
	t.reset();
	t.start();
	hash += shortestDist(ps);
	t.stop();
	maxTime = max(maxTime, t.time);

	if (maxTime > 500) cerr << "too slow: " << maxTime << FAIL;
	cerr << "tested performance: " << maxTime << "ms (hash: " << hash << ")" << endl;
}*/

int main() {
	test_check(10);
	test_check(100);
	test_check(1000);
	test_check(10000);
	//performance_test();
}
