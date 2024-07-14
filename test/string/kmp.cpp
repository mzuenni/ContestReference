#include "../util.h"
#include <string/kmp.cpp>

vector<int> naive(string_view s) {
	vector<int> res(sz(s) + 1, -1);
	for (int i = 0; i < sz(s); i++) {
		for (int j = 0; j <= i; j++)
			if (s.substr(0, j) == s.substr(i-j+1, j))
				res[i+1] = j;
	}
	return res;
}

void stress_test_preprocessing() {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 15);
		auto s = Random::string(n, "abc");
		auto got = kmpPreprocessing(s);
		auto expected = naive(s);
		if (got != expected) cerr << "  error" << FAIL;
		queries += n;
	}
	cerr << "  tested random queries: " << queries << endl;
}

constexpr int N = 10'000'000;
void performance_test_preprocessing() {
	timer t;
	auto s = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$#");
	t.start();
	auto res = kmpPreprocessing(s);
	t.stop();
	hash_t hash = 0;
	for (int x : res) hash += x;
	if (t.time > 500) cerr << "  too slow: " << t.time << FAIL;
	cerr << "  tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

vector<int> naive(string_view s, string_view sub) {
	vector<int> res;
	auto pos = s.find(sub);
	while (pos != string_view::npos) {
		res.push_back(pos);
		pos = s.find(sub, pos + 1);
	}
	return res;
}

void stress_test_kmp() {
	ll queries = 0;
	auto a = Random::string(10'000, "abc");
	for (int tries = 0; tries < 10'000; tries++) {
		int n = Random::integer<int>(1, 10);
		auto b = Random::string(n, "abc");
		auto got = kmpSearch(a, b);
		auto expected = naive(a, b);
		if (got != expected) cerr << "  error" << FAIL;
		queries += got.size();
	}
	cerr << "  tested random queries: " << queries << endl;
}

void performance_test_kmp() {
	timer t;
	auto s = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$#");
	auto sub1 = Random::string(N/2, "a");
	auto sub2 = Random::string(N/2, "ab");
	hash_t hash = 0;
	t.start();
	hash += kmpSearch(s, sub1).size();
	hash += kmpSearch(s, sub2).size();
	t.stop();
	if (t.time > 500) cerr << "  too slow: " << t.time << FAIL;
	cerr << "  tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	cerr << "preprocessing:" << endl;
	stress_test_preprocessing();
	performance_test_preprocessing();
	cerr << "kmp:" << endl;
	stress_test_kmp();
	performance_test_kmp();
}
