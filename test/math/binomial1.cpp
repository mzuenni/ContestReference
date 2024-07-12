#include "../util.h"
#include <math/binomial1.cpp>


void stress_test() {
	vector<ll> last = {1};
	ll queries = 0;
	for (ll i = 0; i <= 61; i++) {
		for (ll j = 0; j <= i; j++) {
			ll got = calc_binom(i, j);
			ll expected = last[j];
			if (got != expected) cerr << "calc_binom(" << i << ", " << j << "), got: " << got << ", expected: " << expected << FAIL;
		}
		queries += sz(last);

		last.push_back(1);
		for (ll j = i; j > 0; j--) {
			last[j] = last[j] + last[j - 1];
		}
	}
	cerr << "tested queries: " << queries << endl;
}

int main() {
	stress_test();
}

