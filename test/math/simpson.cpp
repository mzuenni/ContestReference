#include "../util.h"
std::function<double(double)> f;
constexpr double EPS = 1e-9;
#include <math/simpson.cpp>

struct RandomPolynom {
	vector<double> polynom;
	RandomPolynom(int deg) : polynom(deg) {
		for (auto& x : polynom) x = Random::real<double>(-100, 100);
	}
	double operator()(double x) const {
		double res = 0;
		double xx = 1;
		for (double y : polynom ) {
			res += xx * y;
			xx *= x;
		}
		return res;
	}
	double area(double a, double b) const {
		double res = 0;
		double aa = a;
		double bb = b;
		ll d = 1;
		for (double y : polynom) {
			res += bb / d * y;
			res -= aa / d * y;
			aa *= a;
			bb *= b;
			d++;
		}
		return res;
	}
};

void stress_test() {
	timer t;
	ll queries = 0;
	for (int tries = 0; tries < 1'000; tries++) {
		ll n = Random::integer<ll>(0, 6);
		RandomPolynom poly(n);
		f = poly;
		for (ll i = 0; i < 200; i++) {
			double l = Random::real<double>(-20, 20);
			double r = Random::real<double>(-20, 20);
			if (l > r) swap(l, r);

			t.start();
			double got = integrate(l, r);
			t.stop();
			double expected = poly.area(l, r);
			if (float_error(got, expected) > 1e-6) cerr << fixed << setprecision(20) << "got: " << got << ", expected: " << expected << FAIL;
			queries++;
		}
	}
	if (t.time > 5000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested random queries: " << queries << " (" << t.time << "ms)" << endl;
}

int main() {
	stress_test();
}

