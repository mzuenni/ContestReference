ll calc_binom(ll n, ll k) {
	ll r = 1, d;
	if (k > n) return 0;
	// Reihenfolge garantiert Teilbarkeit
	for (d = 1; d <= k; d++) {
		r *= n--;
		r /= d;
	}
	return r;
}
