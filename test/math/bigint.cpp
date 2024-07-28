#include "../util.h"
#include <math/bigint.cpp>

template<ll MOD>
struct modInt {
	ll value = 0;
	modInt() {}
	modInt(const bigint& x) {
		stringstream a;
		a << x;
		string b = a.str();
		for (ll i = b[0] == '-' ? 1 : 0; i < sz(b); i++) {
			value *= 10;
			value += b[i] - '0';
			value %= MOD;
		}
		if (b[0] == '-') value = (MOD - value) % MOD;
	}

	modInt(ll x) : value(((x % MOD) + MOD) % MOD) {}

	modInt operator+(modInt o) const {return value + o.value;}
	modInt operator-(modInt o) const {return value - o.value;}
	modInt operator*(modInt o) const {return value * o.value;}

	modInt& operator+=(modInt o) {return *this = *this + o;}
	modInt& operator-=(modInt o) {return *this = *this - o;}
	modInt& operator*=(modInt o) {return *this = *this * o;}

	ll& operator*() {return value;}
	bool operator==(const modInt& o) const {return value == o.value;}
	bool operator!=(const modInt& o) const {return value != o.value;}
};

constexpr ll MOD = 1'394'633'899;
constexpr ll POOL = 8;

void stress_test() {
	int queries = 0;
	for (int tries = 0; tries < 1000; tries++) {
		vector<modInt<MOD>> expectedPool(POOL);
		vector<bigint> gotPool(POOL);
		for (int i = 0; i < POOL; i++) {
			ll x = Random::integer<ll>(-1'000'000'000'000'000'000ll, 1'000'000'000'000'000'000ll);
			expectedPool[i] = x;
			gotPool[i] = x;
			if (expectedPool[i] != modInt<MOD>(gotPool[i])) cerr << "error: 0" << FAIL;
		}
		for (int i = 0; i < 200; i++) {
			int a = Random::integer<int>(0, POOL);
			int b = Random::integer<int>(0, POOL);
			int o = Random::integer<int>(0, 3);

			if (Random::integer<int>(0, 2) == 0) {//x=
				auto tmpExpected = expectedPool[a];
				auto tmpGot = gotPool[a];

				if (o == 0) {
					tmpExpected += expectedPool[b];
					tmpGot += gotPool[b];
				}
				if (o == 1) {
					tmpExpected -= expectedPool[b];
					tmpGot -= gotPool[b];
				}
				if (o == 2) {
					tmpExpected -= expectedPool[b];
					tmpGot -= gotPool[b];
				}

				if (tmpExpected != modInt<MOD>(tmpGot)) {
					cerr << gotPool[a];
					if (o == 0) cerr << "+";
					if (o == 1) cerr << "-";
					if (o == 2) cerr << "*";
					cerr << gotPool[b] << "=" << tmpGot << endl;
					cerr << "error: 1" << FAIL;
				}

				expectedPool[b] = tmpExpected;
				gotPool[b] = tmpGot;
			} else {//x
				int c = Random::integer<int>(0, POOL);

				modInt<MOD> tmpExpected;
				bigint tmpGot;

				if (o == 0) {
					tmpExpected = expectedPool[a] + expectedPool[b];
					tmpGot = gotPool[a] + gotPool[b];
				}
				if (o == 1) {
					tmpExpected = expectedPool[a] - expectedPool[b];
					tmpGot = gotPool[a] - gotPool[b];
				}
				if (o == 2) {
					tmpExpected = expectedPool[a] * expectedPool[b];
					tmpGot = gotPool[a] * gotPool[b];
				}

				if (tmpExpected != modInt<MOD>(tmpGot)) {
					cerr << gotPool[a];
					if (o == 0) cerr << "+";
					if (o == 1) cerr << "-";
					if (o == 2) cerr << "*";
					cerr << gotPool[b] << "=" << tmpGot << endl;
					cerr << "error: 2" << FAIL;
				}

				expectedPool[c] = tmpExpected;
				gotPool[c] = tmpGot;
			}
			queries++;
		}
	}
	cerr << "tested random queries: " << queries << endl;
}
	
int main() {
	stress_test();
}

