constexpr ll lim = 10'000'000;
ll fac[lim], inv[lim];

void precalc() {
	fac[0] = inv[0] = 1;
	for (int i = 1; i < lim; i++) fac[i] = fac[i-1] * i % mod;
	inv[lim - 1] = multInv(fac[lim - 1], mod);
	for (int i = lim - 1; i > 0; i--) inv[i-1] = inv[i] * i % mod;
}

ll calc_binom(ll n, ll k) {
	if (n < 0 || n < k || k < 0) return 0;
	return (fac[n] * fac[n-k] % mod) * fac[k] % mod;
}
