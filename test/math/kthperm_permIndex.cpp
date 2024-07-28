#include "../util.h"
#include <datastructures/pbds.cpp>
#include <math/kthperm.cpp>
#include <math/permIndex.cpp>

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		ll n = Random::integer<ll>(20, 1000);
		ll expected = Random::integer<ll>(0, 1'000'000'000'000'000'000);
		ll got = permIndex(kthperm(n, expected));
		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "tested queries: " << queries << endl;
}

int main() {
	stress_test();
}

