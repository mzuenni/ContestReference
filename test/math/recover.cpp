#include "../util.h"
#include <math/recover.cpp>
#include <math/shortModInv.cpp>

void stress_test() {
	ll queries = 0;
	timer t;
	for (int i = 0; i < 500; i++) {
		ll p = Random::prime<ll>(10000);
		for (ll j = 0; 2*j*j < p; j++) {
			for (ll b = 1; 2*b*b < p; b++) {
				if (gcd(j, b) != 1) continue;
				for (ll a : {-j, j}) {
					ll c = a * multInv(b, p);
					
					t.start();
					auto [x, y] = recover(c, p);
					t.stop();

					if (a != x || b != y) cerr << "got: " << x << "/" << y << ", expected: " << a << "/" << b << FAIL;
					queries++;
				}
			}
		}
		for (ll c = 0; c < p; c++) {
			t.start();
			auto [x, y] = recover(c, p);
			t.stop();

			if (y < 0) continue;
			if (y == 0) cerr << "error: y=0" << FAIL;
			ll got = (((x * multInv(y, p)) % p) + p) % p;
			if (got != c) cerr << "got: " << got << ", expected: " << c << FAIL;
			queries++;
		}
	}
	cerr << "tested random queries: " << queries << endl;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms" << endl;
}

int main() {
	stress_test();
}
