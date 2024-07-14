#include "../util.h"
#include <string/suffixArray.cpp>

vector<int> naive(string_view s) {
	vector<int> SA(sz(s));
	iota(all(SA), 0);
	sort(all(SA), [s](int a, int b){
		return s.substr(a) < s.substr(b);
	});
	return SA;
}

int lcp(string_view s, int x, int y) {
	int res = 0;
	while (x + res < sz(s) && y + res < sz(s) && s[x + res] == s[y + res]) res++;
	return res;
}

void stress_test() {
	ll queries = 0;
	for (int i = 0; i < 100; i++) {
		int n = Random::integer<int>(1, 100);
		auto s = Random::string(n, "abc");
		SuffixArray sa(s);
		vector<int> got = sa.SA;
		vector<int> expected = naive(s);
		vector<int> SA(n);
		if (got != expected) cerr << "error: SA" << FAIL;
		got = sa.LCP;
		swap(SA, expected);
		for (int x = 0; x < n; x++) {
			for (int y = 0; y < n; y++) {
				int gotLCP = sa.lcp(x, y);
				int expectedLCP = lcp(s, x, y);
				if (gotLCP != expectedLCP) cerr << "error: lcp" << FAIL;
			}
			if (x > 0) expected[x] = lcp(s, SA[x-1], SA[x]);
		}
		if (got != expected) cerr << "error: LCP" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 200'000;
void performance_test() {
	timer t;
	auto s = Random::string(N, "a") + Random::string(N, "ab") + Random::string(N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$#");
	t.start();
	SuffixArray sa(s);
	t.stop();
	hash_t hash = 0;
	for (int i = 0; i < sz(sa.SA); i++) hash += i*sa.SA[i];
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
