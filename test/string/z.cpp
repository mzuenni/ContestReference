#include "../util.h"
#include <string/z.cpp>

vector<int> naive(const string& s) {
	vector<int> res(sz(s));
	for (int i = 1; i < sz(s); i++) {
		while (i + res[i] < sz(s) && s[res[i]] == s[i + res[i]]) res[i]++;
	}
	return res;
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 15);
		auto s = Random::string(n, "abc");
		auto got = Z(s);
		auto expected = naive(s);
		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 10'000'000;
void performance_test() {
	timer t;
	auto s = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$#");
	t.start();
	auto res = Z(s);
	t.stop();
	hash_t hash = 0;
	for (int x : res) hash += x;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
