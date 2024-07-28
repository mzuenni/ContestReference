#include "../util.h"
namespace got {
#include <graph/bitonicTSP.cpp>
}
namespace expected {
#include <graph/bitonicTSPsimple.cpp>
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 200'000; tries++) {
		int n = Random::integer<int>(1, 30);

		vector<vector<double>> dist(n);
		for (auto& v : dist) v = Random::reals<double>(n, 0, 1e18);

		got::dist = dist;
		expected::dist = dist;

		auto got = got::bitonicTSP();
		auto expected = got::bitonicTSP();

		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

//this is an easy graph...
constexpr int N = 5'000;
void performance_test() {
	timer t;
	got::dist = vector<vector<double>>(N);
	for (auto& v : got::dist) v = Random::reals<double>(N, 0, 1e18);


	t.start();
	auto got = got::bitonicTSP();
	t.stop();
	hash_t hash = 0;
	for (auto x : got) hash += x;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
