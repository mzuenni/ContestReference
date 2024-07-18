ll legendre(ll a, ll p) { // p prim >= 2
	ll s = powMod(a, p / 2, p);
	return s < 2 ? s : -1ll;
}
