#include "../util.h"
#include <string/lyndon.cpp>

bool isLyndon(string_view s) {
	string t = string(s) + string(s);
	for (ll i = 1; i < sz(s); i++) {
		if (s >= t.substr(i, sz(s))) return false;
	}
	return !s.empty();
}

vector<string> naive(ll n, char mi, char ma) {
	vector<string> res;
	auto dfs = [&](auto&& self, string pref)->void{
		if (sz(pref) <= n && isLyndon(pref)) res.push_back(pref);
		if (sz(pref) >= n) return;
		for (char c = mi; c <= ma; c++) {
			self(self, pref + c);
		}
	};
	dfs(dfs, "");
	return res;
}

vector<string> fast(ll n, char mi, char ma) {
	vector<string> res;
	string tmp(1, mi);
	do {
		res.push_back(tmp);
	} while (next(tmp, n, mi, ma));
	return res;
}

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 6);
		auto [l, r] = Random::pair<char>('a', 'f');
		auto got = fast(n, l, r);
		auto expected = naive(n, l, r);
		if (got != expected) cerr << "error" << FAIL;
		queries += sz(expected);
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 9;
void performance_test() {
	timer t;
	t.start();
	auto res = fast(N, 'a', 'f');
	t.stop();
	hash_t hash = sz(res);
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
