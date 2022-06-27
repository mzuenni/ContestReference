ll legendre(ll a, ll p) {
	ll s = powMod(a, p / 2, p);
	return s < 2 ? s : -1ll;
}
