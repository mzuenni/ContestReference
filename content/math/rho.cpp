using lll = __int128;
ll rho(ll n) { // Findet Faktor < n, nicht unbedingt prim.
	if (n % 2 == 0) return 2;
	ll x = 0, y = 0, prd = 2, i = n/2 + 7;
	auto f = [&](lll c){return (c * c + i) % n;};
	for (ll t = 30; t % 40 || gcd(prd, n) == 1; t++) {
		if (x == y) x = ++i, y = f(x);
		if (ll q = (lll)prd * abs(x-y) % n; q) prd = q;
		x = f(x); y = f(f(y));
	}
	return gcd(prd, n);
}

void factor(ll n, map<ll, int>& facts) {
	if (n == 1) return;
	if (isPrime(n)) {facts[n]++; return;}
	ll f = rho(n);
	factor(n / f, facts); factor(f, facts);
}
