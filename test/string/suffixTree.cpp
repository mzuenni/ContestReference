#include "../util.h"
#include <string/suffixTree.cpp>

vector<string> naive(string_view s) {
	vector<string> res(sz(s));
	for (ll i = 0; i < sz(s); i++) {
		res[i] = s.substr(i);
	}
	return res;
}

void stress_test() {
	ll queries = 0;
	for (int i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 15);
		auto s = Random::string(n, "abc") + "#";
		SuffixTree st(s);
		vector<string> got(n + 1);
		auto dfs = [&](auto&& self, string pref, ll node) -> void {
			auto& [l, r, _, next] = st.tree[node];
			if (l >= 0) pref += s.substr(l, r - l);
			if (pref.back() == '#') got[n + 1 - sz(pref)] = pref;
			for (auto [__, j] : next) {
				self(self, pref, j);
			}
		};
		dfs(dfs, "", 0);
		auto expected = naive(s);
		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 200'000;
void performance_test() {
	timer t;
	auto s = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$#");
	t.start();
	SuffixTree st(s);
	t.stop();
	hash_t hash = sz(st.tree);
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
