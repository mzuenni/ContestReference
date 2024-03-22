ll multInv(ll x, ll m) {
	auto [d, a, b] = extendedEuclid(x, m); // Implementierung von oben.
	return ((a % m) + m) % m;
}
