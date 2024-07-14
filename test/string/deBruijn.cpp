#include "../util.h"
#include <string/lyndon.cpp>
#include <string/deBruijn.cpp>

bool isDeBruijn(string s, int n, int k) {
	ll expected = 1;
	for (ll i = 0; i < n; i++) expected *= k;
	if (expected != sz(s)) return false;
	s += s;
	set<string_view> seen;
	for (ll i = 0; 2*i < sz(s); i++) {
		seen.insert(string_view(s).substr(i, n));
	}
	return sz(seen) == expected;
}

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 1000; i++) {
		int n = Random::integer<int>(1, 9);
		auto [l, r] = Random::pair<char>('b', 'f');
		auto got = deBruijn(n, l, r);
		if (!isDeBruijn(got, n, r - l + 1)) cerr << "error" << FAIL;
		queries += sz(got);
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 26;
void performance_test() {
	timer t;
	t.start();
	auto res = deBruijn(N, '0', '1');
	t.stop();
	hash_t hash = sz(res);
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
