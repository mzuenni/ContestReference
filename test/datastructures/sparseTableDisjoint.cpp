#include "../util.h"
#include <datastructures/sparseTableDisjoint.cpp>

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 1000; tries++) {
		int n = Random::integer<int>(1, 100);
		vector<ll> naive = Random::integers<ll>(n, -1000, 1000);
		DisjointST st;
		st.init(&naive);
		for (int operations = 0; operations < 1000; operations++) {
			queries++;
			int l = Random::integer<int>(0, n+1);
			int r = Random::integer<int>(0, n+1);

			ll got = st.query(l, r);
			ll expected = 0;
			for (int j = l; j < r; j++) expected += naive[j];
			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 1'250'000;
void performance_test() {
	timer t;
	vector<ll> naive = Random::integers<ll>(N, -1000, 1000);
	t.start();
	DisjointST st;
	st.init(&naive);
	t.stop();
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		auto [l, r] = Random::pair<int>(0, N+1);
		
		t.start();
		hash += st.query(l, r);
		t.stop();
	}
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
