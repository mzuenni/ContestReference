#include "../util.h"
#include <other/fastSubsetSum.cpp>

int subsetSum(vector<int> w, int t){
	vector<bool> dp(t+1);
	dp[0] = true;
	for(int x : w){
		for(int i = t; i >= x; i--){
			dp[i] = dp[i] || dp[i-x];
		}
	}
	int ma = 0;
	for(int i = 0; i <= t; i++){
		if(dp[i]) ma = i;
	}
	return ma;
}

void stress_test() {
	int queries = 0;
	for (int test = 0; test < 10'000; test++) {
		int n = Random::integer<int>(1, 20);
		int t = Random::integer<int>(1, 500);
		vector<int> w = Random::integers<int>(n, 0, 50);
		int got = fastSubsetSum(w, t);
		int expected = subsetSum(w, t);
		if(got != expected) cerr << "got: " << got << " expected: " << expected << FAIL;
		queries++;
	}
	cerr << "tested queries: " << queries << endl;
}

void performance_test() {
	timer t;
	int n = 10'000, a = 10'000;
	vector<int> w = Random::integers<int>(n, 0, a);
	int target = 10'000'000;
	t.start();
	hash_t hash = fastSubsetSum(w, target);
	t.stop();
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

