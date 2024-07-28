#include "../util.h"
#include <string/manacher.cpp>

vector<int> naive(string_view s) {
	vector<int> res(2 * sz(s) + 1);
	for (int i = 0; i < sz(s); i++) { //odd palindromes
		int j = 2*i+1;
		while (i+res[j] < sz(s) && i-res[j] >= 0 && s[i-res[j]] == s[i+res[j]]) res[j]++;
		res[j]*=2;
		res[j]--;
	}
	for (int i = 0; i <= sz(s); i++) { //even palindromes
		int j = 2*i;
		while (i+res[j] < sz(s) && i-res[j]-1 >= 0 && s[i-res[j]-1] == s[i+res[j]]) res[j]++;
		res[j] *= 2;
	}
	return res;
}

void stress_test() {
	ll queries = 0;
	for (int i = 0; i < 10'000; i++) {
		int n = Random::integer<int>(1, 100);
		auto s = Random::string(n, "abc");
		vector<int> got = manacher(s);
		vector<int> expected = naive(s);
		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 5'000'000;
void performance_test() {
	timer t;
	auto s = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$#");
	t.start();
	auto got = manacher(s);
	t.stop();
	hash_t hash = 0;
	for (int x : got) hash += x;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
