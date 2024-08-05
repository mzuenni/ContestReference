#include "../util.h"
struct MCH {
	#include <datastructures/monotonicConvexHull.cpp>
};

struct Line {
	ll m, c;
	Line(ll m_, ll c_) : m(m_), c(c_) {}
	ll operator()(ll x) {return m*x+c;}
};

void stress_test(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 1000; tries++) {
		int n = Random::integer<int>(1, 100);
		auto ms = Random::distinct<ll>(n, -range, range);
		sort(all(ms), greater<>{});
		auto xs = Random::distinct<ll>(n*100, -range*n, range*n);
		sort(all(xs));
		int i = 0;

		vector<Line> naive;

		MCH mch;
		for (ll m : ms) {
			ll c = Random::integer<ll>(-1000, 1000);
			mch.add(m, c);
			naive.emplace_back(m, c);

			for (int j = i + 100; i < j; i++) {
				ll x = xs[i];

				ll got = mch.query(x);
				ll expected = naive[0](x);
				for (auto l : naive) expected = min(expected, l(x));

				if (got != expected) {
					for (auto l : naive) cerr << l.m << "*x+" << l.c << endl;
					cerr << x << ": " << got << " " << expected << endl;
				}

				if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
				queries++;
			}
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	auto ms = Random::distinct<ll>(N, -1'000'000'000, 1'000'000'000);
	sort(all(ms), greater<>{});
	auto xs = Random::distinct<ll>(N, -1'000'000'000, 1'000'000'000);
	sort(all(xs));
	MCH mch;

	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll c = Random::integer<ll>(-1'000'000'000, 1'000'000'000);
		ll m = ms[operations];
		ll x = xs[operations];
		
		t.start();
		mch.add(m, c);
		hash += mch.query(x);
		t.stop();
	}
	if (t.time > 100) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test(100);
	stress_test(1'000);
	stress_test(1'000'000);
	performance_test();
}
