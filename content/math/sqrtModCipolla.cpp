ll sqrtMod(ll a, ll p) {// teste mit legendre ob lösung existiert
	if (a < 2) return a;
	ll t = 0;
	while (legendre((t*t-4*a) % p, p) >= 0) t = rng() % p;
	ll b = -t, c = -t, d = 1, m = p;
	for (m++; m /= 2; b = (a+a-b*b) % p, a = (a*a) % p) {
		if (m % 2) {
			d = (c-d*b) % p;
			c = (c*a) % p;
		} else {
			c = (d*a - c*b) % p;
	}}
	return (d + p) % p;
}
