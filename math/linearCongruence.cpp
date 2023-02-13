ll solveLinearCongruence(ll a, ll b, ll m) {
	ll g = gcd(a, m);
	if (b % g != 0) return -1;
	return ((b / g) * multInv(a / g, m / g)) % (m / g);
}
