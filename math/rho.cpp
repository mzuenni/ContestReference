ll rho(ll n) { // Findet Faktor < n, nicht unbedingt prim.
	if (n % 2 == 0) return 2;
	ll c = rand() % n, x = rand() % n, y = x, d = 1;
	                           // mulmod or int128
	auto f = [&](ll x){return ((x * x) % n + c) % n;};
	while (d == 1) {
		x = f(x); y = f(f(y));
		d = gcd(abs(x - y), n);
	}
	return d == n ? rho(n) : d;
}

void factor(ll n, map<ll, int>& facts) {
	if (n == 1) return;
	if (isPrime(n)) {
		facts[n]++;
		return;
	}
	ll f = rho(n);
	factor(n / f, facts);
	factor(f, facts);
}
