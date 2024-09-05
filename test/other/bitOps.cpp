#include "../util.h"
#include <other/bitOps.cpp>

void test_subsets() {
	int queries = 0;
	for (int i = 0; i < 1000'000; i++) {
		int mask = 0;
		int limBits = Random::integer<int>(1, 15);
		for (int j = 0; j < limBits; j++) {
			mask |= 1 << Random::integer<int>(0, 31);
		}

		int expeced = 1 << __builtin_popcount(mask);
		int last = -1;
		int seen = 1;
		subsets(mask, [&](int active){
			if (active <= 0) cerr << "error active: " << active << FAIL;
			if (last >= 0 && active >= last) cerr << "error active: " << active  << ", last: " << last << FAIL;
			last = active;
			seen++;
		});
		if (expeced != seen) cerr << "got: " << seen << ", expeced: " << expeced << FAIL;
		queries++;
	}
	cerr << "tested subsets queries: " << queries << endl;
}

ll naive(ll x) {
	vector<ll> bits;
	for (ll i = 0; i < 64; i++) {
		bits.push_back(x & 1);
		x >>= 1;
	}
	reverse(all(bits));
	next_permutation(all(bits));
	reverse(all(bits));
	x = 0;
	for (ll i = 0, j = 1; i < 64; i++, j <<= 1) {
		if (bits[i] != 0) x |= j;
	}
	return x;
}

void test_nextPerm() {
	int queries = 0;
	for (int i = 0; i < 1000'000; i++) {
		ll x = 4;//Random::integer<ll>(1, LL::INF);
		ll got = nextPerm(x);
		ll expeced = naive(x);
		if (got != expeced) cerr << x << ": got: " << got << ", expeced: " << expeced << FAIL;
		queries++;
	}
	cerr << "tested nextPerm queries: " << queries << endl;
}

int main() {
	test_subsets();
	test_nextPerm();
}