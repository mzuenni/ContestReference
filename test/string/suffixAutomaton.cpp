#include "../util.h"
#include <string/suffixAutomaton.cpp>

pair<int, int> naive(string_view s, string_view t) {
	int pos = 0;
	int len = 0;
	for (int j = 0; j < sz(t); j++) {
		for (int i = 0; i < sz(s); i++) {
			int cur = 0;
			while (i+cur < sz(s) && j+cur < sz(t) && s[i+cur] == t[j+cur]) cur++;
			if (cur > len) {
				pos = j;
				len = cur;
			}
		}
	}
	return {pos, len};
}

void stress_test() {
	ll queries = 0;
	for (int i = 0; i < 1000; i++) {
		int n = Random::integer<int>(1, 100);
		auto s = Random::string(n, "abc");
		SuffixAutomaton sa(s);
		for (int j = 0; j < 1000; j++) {
			int m = Random::integer<int>(1, 100);
			auto t = Random::string(m, "abc");
			auto got = sa.longestCommonSubstring(t);
			auto expected = naive(s, t);
			if (got != expected) cerr << "error" << FAIL;
			queries += m;
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 500'000;
void performance_test() {
	timer t;
	auto s = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyz");
	t.start();
	SuffixAutomaton sa(s);
	t.stop();
	hash_t hash = 0;
	for (ll c = 0; c < sz(s);) {
		int m = Random::integer<int>(1, 1000);
		s = Random::string(m, "abc");
		t.start();
		auto [p, l] = sa.longestCommonSubstring(s);
		t.stop();
		hash += l + p;
		c += m;
	}
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
