#include "../util.h"
#include <string/rollingHashCf.cpp>

constexpr ll RandomQ = 318LL << 53;

string thueMorse(ll n) {
	string res = "a";
	while (sz(res) < n) {
		string tmp = res;
		for (char& c : tmp) c ^= 1;
		res += tmp;
	}
	return res;
}

auto getHash(const string& s) {
	return Hash(s, RandomQ)(0, sz(s));
}

void testThueMorse() {
	set<decltype(getHash(""))> got;
	set<string> expected;
	string s = thueMorse(1000);
	Hash h(s, RandomQ);
	for (int l = 0; l < sz(s); l++) {
		for (int r = l + 1; r <= sz(s); r++) {
			got.insert(h(l, r));
			expected.insert(s.substr(l, r - l));
		}
	}
	if (sz(got) != sz(expected)) cerr << "error: thueMorse" << FAIL;
	cerr << "thueMorse: ok" << endl;
}

void testTiny() {
	if (getHash("aa") == getHash("a")) cerr << "error: tiny" << FAIL;
	if (getHash("00") == getHash("0")) cerr << "error: tiny" << FAIL;
	if (getHash("AA") == getHash("A")) cerr << "error: tiny" << FAIL;
	cerr << "tiny: ok" << endl;
}

void testSmall() {
	set<decltype(getHash(""))> got;
	ll expected = 0;
	auto dfs = [&](auto&& self, string pref)->void {
		expected++;
		got.insert(getHash(pref));
		if(sz(pref) >= 5) return;
		for (char c = 'a'; c <= 'z'; c++) {
			self(self, pref + c);
		}
	};
	dfs(dfs, "");
	if (sz(got) != expected) cerr << "error: small" << FAIL;
	cerr << "small: ok" << endl;
}

void stress_test() {
	set<decltype(getHash(""))> got;
	set<string> expected;
	string s = Random::string(1000, "abc");
	Hash h(s, RandomQ);
	for (int l = 0; l < sz(s); l++) {
		for (int r = l + 1; r <= sz(s); r++) {
			got.insert(h(l, r));
			expected.insert(s.substr(l, r - l));
		}
	}
	if (sz(got) != sz(expected)) cerr << "error: stress test" << FAIL;
	cerr << "stress test: ok" << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	auto s = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$#");
	hash_t hash = 0;
	t.start();
	Hash h(s, RandomQ);
	for (ll i = 0; i < N; i++) {
		hash += h(i, i + 2*N);
	}
	t.stop();
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	testThueMorse();
	testTiny();
	testSmall();
	stress_test();
	performance_test();
}
