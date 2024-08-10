#include "../util.h"
constexpr double PI = acos(-1.0);
#pragma GCC diagnostic ignored "-Wshadow"
#include <geometry/spheres.cpp>

void test_consistent() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto pLat = Random::real<double>(-180, 180);
		auto pLon = Random::real<double>(0, 360);
		auto qLat = Random::real<double>(-180, 180);
		auto qLon = Random::real<double>(0, 360);

		point p(pLat, pLon);
		point q(qLat, qLon);

		auto gotA = gcDist(pLat, pLon, qLat, qLon, 1);
		auto gotB = gcDist(p, q);

		if (abs(gotA - gotB) > 1e-6) cerr << "gotA: " << gotA << ", gotB: " << gotB << FAIL;
		queries++;
	}
	cerr << "tested random: " << queries << endl;
}

int main() {
	test_consistent();
}
