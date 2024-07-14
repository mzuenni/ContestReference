#include "../util.h"
#include <datastructures/pbds.cpp>
#include <math/kthperm.cpp>

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 100);
		vector<ll> expected(n);
		iota(all(expected), 0);
		ll k = 0;
		do {
			auto got = kthperm(n, k);
			if (got != expected) cerr << "error" << FAIL;
			k++;
		} while (k < 100 && next_permutation(all(expected)));
		queries += n;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 500'000;
void performance_test() {
	timer t;
	t.start();
	auto got = kthperm(N, 4'168'751'907'498'170ll);
	t.stop();
	ll hash = 0;
	for (ll i = 0; i < N; i++) hash += i * got[i];
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

