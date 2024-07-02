ll calc_binom(ll n, ll k) {
	if (k > n) return 0;
	ll r = 1;
	for (ll d = 1; d <= k; d++) {// Reihenfolge => Teilbarkeit
		r *= n--, r /= d;
	}
	return r;
}
