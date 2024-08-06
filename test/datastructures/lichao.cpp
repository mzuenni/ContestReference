#include "../util.h"
constexpr ll INF = LL::INF;
#include <datastructures/lichao.cpp>

void stress_test(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 1000; tries++) {
		int n = Random::integer<int>(1, 100);
		xs = Random::distinct<ll>(n, -range, range);
		sort(all(xs));

		vector<ll> naive(n, INF);
		Lichao tree;

		for (int operations = 0; operations < 1000; operations++) {
			{
				ll m = Random::integer<ll>(-100, 100);
				ll c = Random::integer<ll>(-range, range);
				ll l = Random::integer<ll>(-range, range);
				ll r = Random::integer<ll>(-range, range);
				Fun f{m, c};

				tree.segmentInsert(f, l, r);
				for (int i = 0; i < n; i++) {
					if (l <= xs[i] && xs[i] < r) naive[i] = min(naive[i], f(i));
				}
			}
			{
				queries++;
				int i = Random::integer<int>(0, n);
				ll got = tree.query(xs[i]);
				ll expected = naive[i];
				if (got != expected) cerr << xs[i] << endl;
				if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
			}
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 200'000;
void performance_test() {
	timer t;
	xs = Random::distinct<ll>(N, -1'000'000'000, 1'000'000'000);
	sort(all(xs));

	t.start();
	Lichao tree;
	t.stop();

	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {

		ll m = Random::integer<ll>(-1'000'000, 1'000'000);
		ll c = Random::integer<ll>(-1'000'000, 1'000'000);
		ll l = Random::integer<ll>(-1'000'000'000, 1'000'000'000);
		ll r = Random::integer<ll>(-1'000'000'000, 1'000'000'000);
		ll x = xs[Random::integer<int>(N)];
		Fun f{m, c};

		t.start();
		tree.segmentInsert(f, l, r);
		hash ^= tree.query(x);
		t.stop();
	}
	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test(100);
	stress_test(1'000);
	stress_test(1'000'000);
	performance_test();
}
