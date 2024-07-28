#include "../util.h"
constexpr ll EPS = 0;
#define double ll
#define polar polar<ll>
#include <geometry/formulas.cpp>
#undef polar
#undef double
#include <geometry/antipodalPoints.cpp>
#include "../geometry.h"

vector<pair<int, int>> naive(vector<pt> ps) {
	ll n = sz(ps);
	auto test = [&](int i, int j){
		if (dot(ps[j] - ps[i], ps[i - 1] - ps[i]) <= 0) return false;
		if (dot(ps[j] - ps[i], ps[i + 1] - ps[i]) <= 0) return false;
		return true;
	};
	ps.push_back(ps[0]);
	ps.push_back(ps[1]);
	vector<pair<int, int>> res;
	for (ll i = 1; i <= n; i++) {
		for (ll j = 1; j < i; j++) {
			if (test(i, j) && test(j, i)) res.emplace_back(i % n, j % n);
		}
	}
	return res;
}

void stress_test(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(3, 30);
		auto ps = Random::convex(n, range);

		auto got = antipodalPoints(ps);
		for (auto& [a, b] : got) if (a > b) swap(a, b);
		sort(all(got));

		auto expected = naive(ps);
		for (auto& [a, b] : expected) if (a > b) swap(a, b);

		for (auto x : expected) {
			auto it = lower_bound(all(got), x);
			if (it == got.end() || *it != x) cerr << "error" << FAIL;
		}
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 99'000;
void performance_test() {
	timer t;

	auto ps = Random::convex(N, 1'000'000'000);

	t.start();
	auto got = antipodalPoints(ps);
	t.stop();

	hash_t hash = sz(got);
	if (t.time > 50) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test(100);
	stress_test(1'000'000'000);
	performance_test();
}
