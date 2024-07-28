bool isPrimitive(ll g, ll n, ll phi, map<ll, int>& phiFacts) {
	if (g == 1) return n == 2;
	if (gcd(g, n) > 1) return false;
	for (auto [f, _] : phiFacts)
		if (powMod(g, phi / f, n) == 1) return false;
	return true;
}

bool isPrimitive(ll g, ll n) {
	ll phin = phi(n); //isPrime(n) => phi(n) = n - 1
	map<ll, int> phiFacts;
	factor(phin, phiFacts);
	return isPrimitive(g, n, phin, phiFacts);
}

ll findPrimitive(ll n) { //test auf existens geht schneller
	ll phin = phi(n); //isPrime(n) => phi(n) = n - 1
	map<ll, int> phiFacts;
	factor(phin, phiFacts);
	for (ll res = 1; res < n; res++) // oder zufällige Reihenfolge
		if (isPrimitive(res, n, phin, phiFacts)) return res;
	return -1;
}
