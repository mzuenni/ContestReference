#include "../util.h"
#include <math/shortModInv.cpp>
constexpr ll mod = 1'394'633'899;
#include <math/polynomial.cpp>

poly randomPoly(int deg) {
	poly p;
	p.data = Random::integers<ll>(deg + 1, 0, mod);
	return p;
}

ll eval(const vector<ll>& p, ll x) {
	ll res = 0;
	for (ll i = 0, j = 1; i < sz(p); i++, j = (j * x) % mod) {
		res += j * p[i];
		res %= mod;
	}
	return res;
}

void test_eval() {
	int queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int deg = Random::integer<int>(1, 30);
		vector<ll> tmp = Random::integers<ll>(deg + 1, 0, mod);
		poly p(deg);
		for (int i = 0; i <= deg; i++) p[i] = tmp[i];

		for (int i = 0; i <= deg + 7; i++) {
			ll x = Random::integer<ll>(0, mod);

			ll got = p(x);
			ll expected = eval(tmp, x);

			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		}
		queries += deg + 1;
	}
	cerr << "tested eval: " << queries << endl;
}

void test_add() {
	int queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(1, 30);
		auto a = randomPoly(n);
		auto b = randomPoly(m);

		auto c = a;
		c += b;

		if (sz(c) > sz(a) && sz(c) > sz(b)) cerr << "error: wrong degree" << FAIL;

		for (int i = 0; i <= n + m + 7; i++) {
			ll x = Random::integer<ll>(0, mod);

			ll got = c(x);
			ll expected = (a(x) + b(x)) % mod;

			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		}
		queries += n + m;
	}
	cerr << "tested add: " << queries << endl;
}

void test_mul() {
	int queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(1, 30);
		auto a = randomPoly(n);
		auto b = randomPoly(m);

		auto c = a * b;
		if (sz(c) > sz(a) + sz(b) - 1) cerr << "error: wrong degree" << FAIL;

		for (int i = 0; i <= n + m + 7; i++) {
			ll x = Random::integer<ll>(0, mod);

			ll got = c(x);
			ll expected = (a(x) * b(x)) % mod;

			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		}
		queries += n + m;
	}
	cerr << "tested mul: " << queries << endl;
}

void test_shift() {
	int queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(1, 30);
		auto a = randomPoly(n);

		auto b = a << m;
		if (sz(b) > sz(a)) cerr << sz(a) << " " << sz(b) << endl;
		if (sz(b) > sz(a)) cerr << "error: wrong degree" << FAIL;

		for (int i = 0; i <= n + 7; i++) {
			ll x = Random::integer<ll>(0, mod);

			ll got = b(x);
			ll expected = a((x + m) % mod);

			if (got != expected) {
				for (ll y : b.data) cerr << y << " ";
				cerr << endl;
			}
			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		}
		queries += n;
	}
	cerr << "tested shift: " << queries << endl;
}

void test_divmod() {
	int queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(1, 30);
		int m = Random::integer<int>(1, 30);
		auto a = randomPoly(n);
		auto b = randomPoly(m);

		auto [div, rem] = a.divmod(b);
		if (sz(rem) > sz(b)) cerr << "error: wrong degree (rem)" << FAIL;
		if (sz(div) > 1 + max<ll>(0, sz(a) - sz(b))) cerr << "error: wrong degree (div)" << FAIL;

		for (int i = 0; i <= n + m; i++) {
			ll x = Random::integer<ll>(0, mod);
			ll d = multInv(b(x), mod);

			ll got = (div(x) + rem(x) * d) % mod;
			ll expected = (a(x) * d) % mod;

			if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		}
		queries += n + m;
	}
	cerr << "tested divmod: " << queries << endl;
}
	
int main() {
	test_eval();
	test_add();
	test_mul();
	test_shift();
	test_divmod();
}

