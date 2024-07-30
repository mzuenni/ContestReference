#include "../util.h"
#define ll lll
#include <math/modPowIterativ.cpp>
#undef ll
#include <math/millerRabin.cpp>
#include <math/rho.cpp>

map<ll, int> factor(ll n) {
	map<ll, int> facts;
	factor(n, facts);
	return facts;
}

ll mul(const map<ll, int>& facts) {
	ll res = 1;
	for (auto [p, c] : facts) {
		for (int i = 0; i < c; i++) res *= p;
	}
	if (res < 1 || res > (1ll << 62)) cerr << "invalid number: " << res << FAIL;
	return res;
}

void stress_test() {
	vector<map<ll, int>> test = {
		{}, // 1
		{{2, 1}},
		{{3, 1}},
		{{2, 2}},
		{{5, 1}},
		{{2, 1}, {3, 1}},
		{{2, 2}, {3, 1}},
		{{2, 1}, {3, 2}},
		{{2, 2}, {3, 2}},
		{{2, 62}},
		{{2, 18}, {5, 18}},
		{{352523, 1}, {352817, 1}},
		{{41, 1}, {71, 1}, {421, 1}, {811, 1}},
		{{11, 1}, {17, 1}, {31, 1}, {61, 1}, {73, 1}, {66361, 1}},
		{{500000003, 1}, {1999999973, 1}},
		{{65537, 2}},
		{{999665081, 1}, {999716071, 1}},
		{{550177, 1}, {1100353, 1}, {1650529, 1}},
		{{459397, 1}, {918793, 1}, {1378189, 1}},
		{{37, 1}, {109, 1}},
		{{31, 1}, {151, 1}},
		{{239, 1}, {1429, 1}},
		{{89, 1}, {1093, 1}},
		{{2, 3}, {15800133918749317, 1}},
		{{12251, 1}, {85751, 1}},
		{{3, 1}, {5, 3}, {131, 1}, {6855593, 1}},
		{{5, 1}, {1927962474784631, 1}},
		{{197279, 1}, {1775503, 1}},
		{{3716371, 1}, {14865481, 1}},
		{{3, 1}, {5, 1}, {3075593, 1}, {3075593, 1}},
		{{4880401, 1}, {9760801, 1}},
		{{2822159, 1}, {11288633, 1}},
		{{3290341, 1}, {6580681, 1}},
		{{611557, 1}, {1834669, 1}},
		{{9227, 1}, {894923, 1}, {968731, 1}},
		{{3, 4}, {13, 1}, {62633, 2}},
		{{2, 2}, {3, 1}, {5, 1}, {167, 2}, {299197, 2}},
		{{332721269, 1}, {560937673, 1}},
		{{30702523, 1}, {122810089, 1}},
		{{24786439, 1}, {123932191, 1}},
		{{382500329, 1}, {1530001313, 1}},
		{{2, 4}, {5, 4}, {13, 1}, {30839, 2}},
		{{3, 1}, {385417, 1}, {7985344259, 1}},
		{{2, 4}, {3, 1}, {5, 1}, {7, 2}, {61, 1}, {179, 2}, {1381, 2}},
		{{627838711, 1}, {1212379867, 1}},
		{{3, 5}, {5, 3}, {41, 2}, {157321, 2}},
		{{5, 2}, {13, 1}},
		{{3, 1}, {5, 5}},
		{{2, 1}, {73, 1}, {193, 1}},
		{{5, 2}, {13, 1}, {19, 1}, {73, 1}},
		{{2, 3}, {3, 1}, {407521, 1}},
		{{2, 1}, {3, 1}, {299210837, 1}},
		{{2, 8}, {3, 4}, {5, 2}, {7, 2}, {11, 1}, {13, 1}, {17, 1}, {19, 1}, {23, 1}, {29, 1}, {3137, 1}},
	};

	timer t;
	for (auto expected : test) {
		ll x = mul(expected);
		t.start();
		auto got = factor(x);
		t.stop();
		if (got != expected) {
			cerr << "number: " << x << endl;
			cerr << "got:" << endl;
			for (auto [p, c] : got) cerr << p << "^" << c << endl;
			cerr << "expected" << endl;
			for (auto [p, c] : expected) cerr << p << "^" << c << endl;
			cerr << FAIL;
		}
	}
	if (t.time > 100) cerr << "too slow" << FAIL;
	cerr << "stress tested: " << t.time << "ms" << endl;
}

ll randomHard(ll lim) {
	ll root2 = sqrt(lim);
	ll root3 = cbrt(lim);
	ll a = Random::prime<ll>(root2 / 2 - root3, root2 / 2 + root3);
	ll b = Random::prime<ll>(lim / a - root3, lim / a);
	return a * b;
}

constexpr int N = 200;
void performance_test() {
	timer t;
	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
		ll x = randomHard(1e18);
		t.start();
		hash += factor(x).size();
		t.stop();
	}
	if (t.time > 750) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

