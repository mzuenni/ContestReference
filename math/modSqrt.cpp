ll sqrtMod(ll a, ll p) {
	assert(powMod(a, (p + 1)/2, p) == 1); //a ist ein quadrat mod p?
	if (p % 4 == 3) return powMod(a, (p + 1)/2, p);
	if (p % 8 == 5) return powMod(a, (p + 3)/8, p);
	ll s = p - 1;
	ll r = 0;
	while (s % 2 == 0) s /= 2, r++;
	ll n = 2;
	while (powMod(n, (p - 1)/2, p) != p - 1) n++;
	ll x = powMod(a, (s + 1)/2, p);
	ll b = powMod(a, s, p);
	ll g = powMod(n, s, p);
	while (true) {
		ll t = b;
		ll m = 0;
		for (;m < r && t != 1; m++) t = (t * t) % p;
		if (t == 1) return x;
		ll gs = powMod(g, 1ll << (r - m - 1), p);
		g = (gs * gs) % p;
		x = (x * gs) % p;
		b = (b * g) % p;
		r = m;
}}
