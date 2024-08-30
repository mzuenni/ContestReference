#include "../util.h"
#include <other/recover.cpp>
#include <math/shortModInv.cpp>

void stress_test() {
	ll queries = 0;
	timer t;
	for (int i = 0; i < 1000; i++) {
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
		
	}
	cerr << "tested random queries: " << queries << endl;
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms" << endl;
}

int main() {
	stress_test();
}
