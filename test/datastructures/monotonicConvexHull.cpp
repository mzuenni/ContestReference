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
		auto ms = Random::integers<ll>(n, -range, range);
		sort(all(ms), greater<>{});
		auto cs = ms;
		for (int l = 0, r = 0; l < n;) {
			while (r < n && ms[l] == ms[r]) r++;
			auto tmp = Random::distinct<ll>(r - l, -range, range);
			sort(all(tmp), greater<>{});
			for (int c : tmp) {
				cs[l] = c;
				l++;
			}
		}

		auto xs = Random::integers<ll>(n*100, -range*n, range*n);
		sort(all(xs));
		int i = 0;

		vector<Line> naive;

		MCH mch;
		for (int k = 0; k < n; k++) {
			ll m = ms[k];
			ll c = cs[k];

			mch.add(m, c);
			naive.emplace_back(m, c);

			for (int j = i + 100; i < j; i++) {
				ll x = xs[i];

				ll got = mch.query(x);
				ll expected = naive[0](x);
				for (auto l : naive) expected = min(expected, l(x));

				if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
				queries++;
			}
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

void stress_test_independent(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 1000; tries++) {
		int n = Random::integer<int>(1, 100);
		auto ms = Random::integers<ll>(n, -range, range);
		sort(all(ms), greater<>{});
		auto cs = ms;
		for (int l = 0, r = 0; l < n;) {
			while (r < n && ms[l] == ms[r]) r++;
			auto tmp = Random::distinct<ll>(r - l, -range, range);
			sort(all(tmp), greater<>{});
			for (int c : tmp) {
				cs[l] = c;
				l++;
			}
		}

		vector<Line> naive;

		MCH mch;
		for (int i = 0; i < n; i++) {
			ll m = ms[i];
			ll c = cs[i];

			mch.add(m, c);
			naive.emplace_back(m, c);

			auto xs = Random::integers<ll>(100, -range, range);
			sort(all(xs));
			auto tmp = mch;

			for (auto x : xs) {
				ll got = tmp.query(x);
				ll expected = naive[0](x);
				for (auto l : naive) expected = min(expected, l(x));

				if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
				queries++;
			}
		}
	}
	cerr << "tested random independent queries: " << queries << endl;
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
	stress_test_independent(100);
	stress_test_independent(1'000);
	stress_test_independent(1'000'000);
	performance_test();
}
