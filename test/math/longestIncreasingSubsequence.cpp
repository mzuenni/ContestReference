#include "../util.h"
constexpr ll INF = LL::INF;
#include <math/longestIncreasingSubsequence.cpp>
#define lis unstrictLis
#define lower_bound upper_bound
#include <math/longestIncreasingSubsequence.cpp>
#undef lower_bound
#undef lis

template<bool STRICT>
bool isLis(const vector<ll>& a, const vector<int>& lis) {
	for (int i = 1; i < sz(lis); i++) {
		if (lis[i-1] >= lis[i]) return false;
		if (a[lis[i-1]] > a[lis[i]]) return false;
		if (STRICT && a[lis[i-1]] == a[lis[i]]) return false;
	}
	return true;
}

template<bool STRICT>
vector<int> naive(const vector<ll>& a) {
	vector<int> res;
	for (ll i = 1; i < (1ll << sz(a)); i++) {
		vector<int> tmp;
		for (ll j = 0; j < sz(a); j++) {
			if (((i >> j) & 1) != 0) tmp.push_back(j);
		}
		if (sz(tmp) >= sz(res) && isLis<STRICT>(a, tmp)) res = tmp;
	}
	return res;
}

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 12);
		auto a = Random::integers<ll>(n, -10, 10);
		auto expected = naive<true>(a);
		auto got = lis(a);
		if (got != expected) cerr << "error: strict" << FAIL;
		queries += n;
	}
	for (ll i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 12);
		auto a = Random::integers<ll>(n, -10, 10);
		auto expected = naive<false>(a);
		auto got = unstrictLis(a);
		if (got != expected) cerr << "error: not strict" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	auto a = Random::integers<ll>(N, -10'000, 10'000);
	auto b = Random::integers<ll>(N, -10'000, 10'000);
	sort(all(b));
	auto c = Random::integers<ll>(N, -10'000, 10'000);
	sort(all(c));
	reverse(all(c));
	hash_t hash = 0;
	t.start();
	hash += lis(a).size();
	hash += lis(b).size();
	hash += lis(c).size();
	t.stop();
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
