#include "../util.h"
#include <datastructures/pbds.cpp>
#include <math/permIndex.cpp>

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 100);
		vector<ll> cur(n);
		iota(all(cur), 0);
		ll expected = 0;
		do {
			auto got = permIndex(cur);
			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
			expected++;
		} while (expected < 100 && next_permutation(all(cur)));
		queries += n;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 500'000;
void performance_test() {
	timer t;
	vector<ll> cur(N);
	iota(all(cur), 0);
	reverse(cur.end() - 10, cur.end());
	t.start();
	auto hash = permIndex(cur);
	t.stop();
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

