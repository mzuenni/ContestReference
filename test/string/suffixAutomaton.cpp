#include "../util.h"
#include <string/suffixAutomaton.cpp>

pair<int, int> naive(string_view s, string_view t) {
	int pos = 0;
	int len = 0;
	for (int i = 0; i < sz(s); i++) {
		for (int j = 0; j < sz(t); j++) {
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
		int n = Random::integer<int>(1, 5);
		auto s = Random::string(n, "abc");
		SuffixAutomaton sa(s);
		for (int j = 0; j < 1000; j++) {
			int m = Random::integer<int>(1, 5);
			auto t = Random::string(m, "abc");
			auto got = sa.longestCommonSubstring(t);
			auto expected = naive(s, t);
			cout << s << " " << t << endl;
			cout << got.first << " " << expected.first << endl;
			cout << got.second << " " << expected.second << endl;
			if (got != expected) cerr << "error" << FAIL;
			queries += m;
		}
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 200'000;
void performance_test() {
	/*timer t;
	auto s = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$#");
	t.start();
	SuffixArray sa(s);
	t.stop();
	ll hash = 0;
	for (int i = 0; i < sz(sa.SA); i++) hash += i*sa.SA[i];
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;*/
}

int main() {
	stress_test();
	performance_test();
}
