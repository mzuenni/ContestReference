#include "../util.h"
#include <math/primeSieve.cpp>
namespace legendre {
	#include <math/piLegendre.cpp>
}
namespace lehmer {
	#include <math/piLehmer.cpp>
}

void stress_test() {
	int queries = 0;
	for (int i = 0; i < 1'000; i++) {
		ll x = Random::integer<ll>(0, 1'000'000'000);
		auto got = lehmer::pi(x);
		auto expected = legendre::pi(x);
		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested random queries: " << queries << endl;
}

void performance_test() {
	timer t;
	hash_t hash = 0;
	t.start();
	lehmer::init();
	t.stop();
	for (int i = 0; i < 1; i++)  {
		ll x = Random::integer<ll>(0, 1000'000'000'000);
		t.start();
		hash += lehmer::pi(x);
		t.stop();
	}
	if (t.time > 1500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	performance_test();
	stress_test();
}

