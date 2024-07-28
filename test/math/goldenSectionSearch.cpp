#include "../util.h"
#include <math/goldenSectionSearch.cpp>

struct RandomFunction {
	ld min;
	vector<pair<ld, int>> polys;
	RandomFunction(ld l, ld r) : min(Random::real<ld>(l, r)) {
		do {
			polys.emplace_back(
				Random::real<ld>(0, 1e9),
				2 * Random::integer<int>(1, 5)
			);
		} while(false && Random::integer<int>(4) != 0);
	}

	ld operator()(ld x){
		ld res = 0;
		for (auto [m, p] : polys) {
			res += m * pow(x - min, p);
		}
		return res;
	}

	friend ostream& operator<<(ostream& os, const RandomFunction& f) {
		string plus = "";
		for (auto [m, p] : f.polys) {
			os << setprecision(15) << plus << m << "*(x-" << f.min << ")**" << p;
			plus = "+";
		}
		return os;
	}
};

void stress_test() {
	int queries = 0;
	for (int i = 0; i < 50'000; i++) {
		ld l = Random::real<double>(-200, 200);
		ld r = Random::real<double>(-200, 200);
		if (l > r) swap(l, r);

		RandomFunction f(l, r);

		ld got = gss(l, r, f);
		ld expected = f.min;
		if (float_error(got, expected) > 1e-6) {
			cerr << f << endl;
			cerr << "got: " << got << ", expected: " << expected << FAIL;
		}
		queries++;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 10'000;
void performance_test() {
	timer t;
	RandomFunction f(-200, 200);
	f.polys.resize(1);

	hash_t hash = 0;
	for (int i = 0; i < N; i++) {
		t.start();
		hash += gss(-200, 200, f);
		t.stop();
	}
	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

