ll calc_binom(ll n, ll k, ll p) {
	assert(n < p); //wichtig: sonst falsch!
	if (k > n) return 0;
	ll x = k % 2 != 0 ? p-1 : 1;
	for (ll c = p-1; c > n; c--) {
		x *= c - k; x %= p;
		x *= multInv(c, p); x %= p;
	}
	return x;
}
