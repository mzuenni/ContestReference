#include "../util.h"
#include <math/extendedEuclid.cpp>
#include <math/chineseRemainder.cpp>

struct NAIVE {
	vector<pair<ll, ll>> added;
	void add(ll a, ll m) {
		added.emplace_back(a, m);
	}
	ll sol() const {
		ll n = 1;
		for (auto [_, x] : added) n = lcm(n, x);
		for (ll i = 0; i < n; i++) {
			bool ok = true;
			for (auto [a, m] : added) {
				ok &= (i % m) == a;
			}
			if (ok) return i;
		}
		return -1;
	}
};

void stress_test() {
	ll queries = 0;
	ll withSol = 0;
	for (ll i = 0; i < 100'000; i++) {
		CRT crt;
		NAIVE naive;
		for (ll j = 0; j < 3; j++) {
			int m = Random::integer<int>(1, 50);
			int a = Random::integer<int>(0, m);
			crt.add(a, m);
			naive.add(a, m);
		}
		if (crt.hasSol != (naive.sol() >= 0)) cerr << "error" << FAIL;
		if (crt.hasSol && crt.sol != naive.sol()) cerr << "got: " << (ll)crt.sol << ", expected: " << naive.sol() << FAIL;
		queries += crt.M;
		withSol += crt.hasSol;
	}
	cerr << "tested queries: " << queries << "(" << withSol << ")" << endl;
}

int main() {
	stress_test();
}

