ll multInv(ll n, ll p) {
	ll x, y;
	extendedEuclid(n, p, x, y); // Implementierung von oben.
	return ((x % p) + p) % p;
}
