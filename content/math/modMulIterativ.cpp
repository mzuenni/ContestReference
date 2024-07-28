ll mulMod(ll a, ll b, ll n) {
	ll res = 0;
	while (b > 0) {
		if (b & 1) res = (a + res) % n;
		a = (a * 2) % n;
		b /= 2;
	}
	return res;
}
