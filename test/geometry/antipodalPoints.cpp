#include "../util.h"
constexpr ll EPS = 0;
#define double ll
#define polar polar<ll>
#include <geometry/formulas.cpp>
#undef polar
#undef double
#include <geometry/antipodalPoints.cpp>

vector<ll> randomPartition(ll n, std::size_t k){//min = 0;
	n += k;
	vector<ll> res = Random::distinct<ll>(k-1, 1, n);
	sort(all(res));
	res.emplace_back(n);
	ll last = 0;
	for (std::size_t i = 0; i < k; i++) {
		res[i] -= last;
		last += res[i];
		res[i]--;
	}
	return res;
}

#include <geometry/sortAround.cpp>
vector<pt> randomConvex(int n, ll dim) {
	binomial_distribution<int> binomial(n - 2, 0.5);

	while (true) {
		int left = 1 + binomial(Random::rng);
		int down = 1 + binomial(Random::rng);
		auto x = randomPartition(2 * dim - 2, left);
		auto y = randomPartition(2 * dim - 2, down);
		for (auto& z : x) z = -z;
		for (auto& z : y) z = -z;
		for (auto z : randomPartition(2 * dim - 2, n - left)) x.push_back(z);
		for (auto z : randomPartition(2 * dim - 2, n - down)) y.push_back(z);
		auto itX = partition(x.begin(), x.end(), [](ll z){return z == 0;});
		auto itY = partition(y.begin(), y.end(), [](ll z){return z != 0;});
		if (distance(x.begin(), itX) + distance(itY, y.end()) > n) continue;
		shuffle(itX, x.end(), Random::rng);
		if (itX != x.begin()) shuffle(y.begin(), itY, Random::rng);

		vector<pt> dirs(n);
		for (size_t i = 0; i < dirs.size(); i++) {
			dirs[i] = {x[i], y[i]};
		}
		sortAround(0, dirs);

		vector<pt> res = {{0, 0}};
		ll maxX = 0;
		ll maxY = 0;
		for (auto dir : dirs) {
			pt tmp(real(res.back()) + real(dir),
			       imag(res.back()) + imag(dir));
			maxX = std::max(maxX, real(tmp));
			maxY = std::max(maxY, imag(tmp));
			res.emplace_back(tmp);
		}
		res.pop_back();
		for (auto& point : res) {
			point = pt(real(point) + dim - 1 - maxX,
			           imag(point) + dim - 1 - maxY);
		}
		bool strict = true;
		for (int i = 0; i < n; i++) strict &= cross(res[i], res[(i + 1) % n], res[(i + 2) % n]) != 0;
		if (strict) return res;
	}
}

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
		auto ps = randomConvex(n, range);

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

	auto ps = randomConvex(N, 1'000'000'000);

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
