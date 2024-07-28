#include "../util.h"
#define ll lll
#include <math/modPowIterativ.cpp>
#undef ll
#include <math/legendre.cpp>

void stress_test() {
	ll work = 0;
	for (ll i = 0; i < 5'000; i++) {
		ll p = Random::prime<ll>(5'000);
		vector<bool> isSquare(p);
		for (ll j = 1; j < p; j++) isSquare[(j*j) % p] = true;
		for (ll j = 0; j < p; j++) {			
			auto got = legendre(j, p);
			auto expected = j == 0 ? 0 : (isSquare[j] ? 1 : -1);
			if (got != expected) cerr << "error: " << j << " " << p << FAIL;
		}
		work += p;
	}
	cerr << "stress tested: " << work << endl;
}

constexpr int N = 1'000'000;
constexpr ll mod = 1'394'633'899;
void performance_test() {
	timer t;
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll j = Random::integer<ll>(mod);
		t.start();
		hash += legendre(j, mod);
		t.stop();
	}
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}


int main() {
	stress_test();
	performance_test();
}

