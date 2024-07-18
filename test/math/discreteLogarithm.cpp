#include "../util.h"
#include <math/modPowIterativ.cpp>
#include <math/legendre.cpp>

ll overwrite = 0;
ll getMemory(ll /**/) {return overwrite - 1;} //dlog code adds one...
#define sqrtl getMemory
#include <math/discreteLogarithm.cpp>
#undef sqrtl

template<typename F>
void stress_test(F&& f) {
	ll work = 0;
	for (ll tries = 0; tries < 3'000; tries++) {
		ll p = Random::prime<ll>(1'000);
		overwrite = f(p);
		ll a = Random::integer<ll>(1, p);
		vector<bool> naive(p);
		for (ll i = 0, j = 1; i < p; i++, j = (j * a) % p) {
			naive[j] = true;
		}
		for (ll b = 0; b < p; b++) {
			ll got = dlog(a, b, p);
			if (got < -1 || got >= p) cerr << "error: out of range" << FAIL;
			if ((got >= 0) != naive[b]) {
				cerr << a << " " << b << " " << p << endl;
				cerr << got << endl;
				cerr << "error" << FAIL;
			}
			if (got >= 0 && powMod(a, got, p) != b) {
				cerr << a << "^" << got << " = " << powMod(a, got, p) << " != " << b << " % " << p << endl;
				cerr << "error: wrong" << FAIL;
			}
			work++;
		}
	}
	cerr << "stress tested: " << work << endl;
}

constexpr int N = 25;
constexpr ll mod = 1'394'633'899;
void performance_test() {
	timer t;
	hash_t hash = 0;
	overwrite = sqrt(mod);
	for (int operations = 0; operations < N; operations++) {
		ll a = Random::integer<ll>(1, mod);
		ll b = Random::integer<ll>(0, mod);
		t.start();
		hash += dlog(a, b, mod);
		t.stop();
	}
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}


int main() {
	stress_test([](ll p){return sqrtl(p);});
	stress_test([](ll p){return min<ll>(10, p - 1);});
	stress_test([](ll p){return min<ll>(p - 1, sqrtl(p) + 100);});
	performance_test();
}

