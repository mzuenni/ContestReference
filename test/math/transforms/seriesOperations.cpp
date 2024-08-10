#include "../../util.h"
#include <math/modPowIterativ.cpp>
#include <math/transforms/ntt.cpp>
#include <math/transforms/multiplyNTT.cpp>
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <math/transforms/seriesOperations.cpp>

namespace reference {//checked against yosupo
	vector<ll> poly_inv(vector<ll> a, int n){
		vector<ll> q = {powMod(a[0], mod-2, mod)};
		for(int len = 1; len < n; len *= 2){
			vector<ll> a2 = a, q2 = q;
			a2.resize(2*len), q2.resize(2*len);
			ntt(q2);
			for(int j = 0; j < 2; j++){
				ntt(a2);
				for(int i = 0; i < 2*len; i++) a2[i] = a2[i] * q2[i] % mod;
				ntt(a2, true);
				for(int i = 0; i < len; i++) a2[i] = 0;
			}
			for(int i = len; i < min(n, 2*len); i++) q.push_back((mod - a2[i]) % mod);
		}
		return q;
	}

	vector<ll> poly_deriv(vector<ll> a){
		for(int i = 0; i < sz(a)-1; i++)
			a[i] = a[i+1] * (i+1) % mod;
		a.pop_back();
		return a;
	}

	vector<ll> poly_integr(vector<ll> a){
		if(a.empty()) return {0};
		a.push_back(a.back() * powMod(sz(a), mod-2, mod) % mod);
		for(int i = sz(a)-2; i > 0; i--)
			a[i] = a[i-1] * powMod(i, mod-2, mod) % mod;
		a[0] = 0;
		return a;
	}

	vector<ll> poly_log(vector<ll> a, int n){
		a = mul(poly_deriv(a), poly_inv(a, n));
		a.resize(n-1);
		a = poly_integr(a);
		return a;
	}

	vector<ll> poly_exp(vector<ll> a, int n){
		vector<ll> q = {1};
		for(int len = 1; len < n; len *= 2){
			vector<ll> p = poly_log(q, 2*len);
			for(int i = 0; i < 2*len; i++)
				p[i] = (mod - p[i] + (i < sz(a) ? a[i] : 0)) % mod;
			vector<ll> q2 = q;
			q2.resize(2*len);
			ntt(p), ntt(q2);
			for(int i = 0; i < 2*len; i++) p[i] = p[i] * q2[i] % mod;
			ntt(p, true);
			for(int i = len; i < min(n, 2*len); i++) q.push_back(p[i]);
		}
		return q;
	}
}

void test_inv() {
	ll queries = 0;
	for (ll i = 0; i < 50'000; i++) {
		int n = Random::integer<int>(1, 100);
		int m = Random::integer<int>(1, 100);
		vector<ll> a = Random::integers<ll>(n, 0, mod);

		auto got = poly_inv(a, m);
		auto expected = reference::poly_inv(a, m);
		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested inv: " << queries << endl;
}

void test_deriv() {
	ll queries = 0;
	for (ll i = 0; i < 50'000; i++) {
		int n = Random::integer<int>(1, 100);
		vector<ll> a = Random::integers<ll>(n, 0, mod);

		auto got = poly_deriv(a);
		auto expected = reference::poly_deriv(a);
		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested deriv: " << queries << endl;
}

void test_integr() {
	ll queries = 0;
	for (ll i = 0; i < 50'000; i++) {
		int n = Random::integer<int>(1, 100);
		vector<ll> a = Random::integers<ll>(n, 0, mod);

		auto got = poly_deriv(a);
		auto expected = reference::poly_deriv(a);
		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested integr: " << queries << endl;
}

void test_log() {
	ll queries = 0;
	for (ll i = 0; i < 50'000; i++) {
		int n = Random::integer<int>(1, 100);
		int m = Random::integer<int>(1, 100);
		vector<ll> a = Random::integers<ll>(n, 0, mod);

		auto got = poly_log(a, m);
		auto expected = reference::poly_log(a, m);
		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested log: " << queries << endl;
}

void test_exp() {
	ll queries = 0;
	for (ll i = 0; i < 50'000; i++) {
		int n = Random::integer<int>(1, 100);
		int m = Random::integer<int>(1, 100);
		vector<ll> a = Random::integers<ll>(n, 0, mod);

		auto got = poly_exp(a, m);
		auto expected = reference::poly_exp(a, m);
		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested exp: " << queries << endl;
}

int main() {
	test_inv();
	test_deriv();
	test_integr();
	test_log();
	test_exp();
}
