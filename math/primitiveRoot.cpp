bool isPrimitive(ll g, ll n, ll phi, map<ll, int> phiFacs) {
	if (g == 1) return n == 2;
	for (auto& f : phiFacs)
		if (1 == powMod(g, phi / f.first, n)) return false;
	return true;
}

bool isPrimitive(ll g, ll n) {
	ll phin = phi(n); //isPrime(n) => phi(n) = n - 1 
	map<ll, int> phiFacs;
	factor(phin, phiFacs);
	return isPrimitive(g, n, phin, phiFacs);
}

ll findPrimitive(ll n) {
	ll phin = phi(n); //isPrime(n) => phi(n) = n - 1
	map<ll, int> phiFacs;
	factor(phin, phiFacs);
	//auch zufällige Reihenfolge möglich!
	for (ll res = 1; res < n; res++)
		if (isPrimitive(res, n, phin, phiFacs)) return res;
	return -1;
}
