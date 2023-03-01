constexpr ll mod = 1'000'000'009;

ll binomPPow(ll n, ll k, ll p) {
	ll res = 1;
	if (p > n) {
	} else if (p > n - k || (p * p > n && n % p < k % p)) {
		res *= p;
		res %= mod;
	} else if (p * p <= n) {
		ll c = 0, tmpN = n, tmpK = k;
		while (tmpN > 0) {
			if (tmpN % p < tmpK % p + c) {
				res *= p;
				res %= mod;
				c = 1;
			} else c = 0;
			tmpN /= p;
			tmpK /= p;
	}}
	return res;
}

ll calc_binom(ll n, ll k) {
	if (k > n) return 0;
	ll res = 1;
	k = min(k, n - k);
	for (ll i = 0; primes[i] <= n; i++) {
		res *= binomPPow(n, k, primes[i]);
		res %= mod;
	}
	return res;
}
