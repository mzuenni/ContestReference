#include "../util.h"
#include <string/longestCommonSubsequence.cpp>

bool isSubstr(string_view s, string_view sub) {
	int i = 0;
	for (char c : s) {
		if (i < sz(sub) && c == sub[i]) i++;
	}
	return i >= sz(sub);
}

string naive(string_view s, string_view t) {
	string res = "";
	for (ll i = 1; i < (1ll << sz(s)); i++) {
		string tmp;
		for (ll j = 0; j < sz(s); j++) {
			if (((i >> j) & 1) != 0) tmp.push_back(s[j]);
		}
		if (sz(tmp) >= sz(res) && isSubstr(t, tmp)) res = tmp;
	}
	return res;
}

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 12);
		int m = Random::integer<int>(1, 12);
		auto s = Random::string(n, "abc");
		auto t = Random::string(m, "abc");
		auto got = lcss(s, t);
		auto expected = naive(s, t);
		if (got != expected) cerr << s << ", " << t << ", got: " << got << ", expected: " << expected << FAIL;
		queries += n + m;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 2'000;
void performance_test() {
	timer t;
	auto a = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$#");
	auto b = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$#");
	t.start();
	auto res = lcss(a, b);
	t.stop();
	hash_t hash = sz(res);
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
