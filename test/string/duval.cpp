#include "../util.h"
#pragma GCC diagnostic ignored "-Wreturn-type"
#include <string/duval.cpp>

constexpr int N = 20'000'000;

bool isLyndon(string_view s) {
	string t = string(s) + string(s);
	for (ll i = 1; i < sz(s); i++) {
		if (s >= t.substr(i, sz(s))) return false;
	}
	return !s.empty();
}

void stress_test_duval() {
	ll queries = 0;
	for (int i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 100);
		auto s = Random::string(n, "abc");
		vector<pair<int, int>> got = duval(s);
		if (got.empty()) cerr << "error: a" << FAIL;
		if (got.front().first != 0) cerr << "error: b" << FAIL;
		if (got.back().second != n) cerr << "error: c" << FAIL;
		for (int j = 1; j < sz(got); j++) {
			if (got[j - 1].second != got[j].first) cerr << "error: d" << FAIL; 
		}
		for (auto [l, r] : got) {
			if (!isLyndon(string_view(s).substr(l, r-l))) cerr << "error: e" << FAIL; 
		}
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

void performance_test_duval() {
	timer t;
	auto s = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$#");
	t.start();
	auto got = duval(s);
	t.stop();
	hash_t hash = 0;
	for (auto [l, r] : got) hash += l + r;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int naive(string s) {
	ll n = sz(s);
	s += s;
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (string_view(s).substr(i, n) <= string_view(s).substr(res, n)) res = i;
	}
	return res;
}

void stress_test_minrotation() {
	ll queries = 0;
	for (int i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 100);
		auto s = Random::string(n, "abc");
		int got = minrotation(s);
		auto expected = naive(s);
		if (got != expected) cerr << s << ": got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

void performance_test_minrotation() {
	timer t;
	auto s = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$#");
	t.start();
	hash_t hash = minrotation(s);
	t.stop();
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test_duval();
	performance_test_duval();
	stress_test_minrotation();
	performance_test_minrotation();
}
