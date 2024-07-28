ll root(ll a, ll b, ll m) { // a > 0!
	ll g = findPrimitive(m);
	ll c = dlog(powMod(g, a, m), b, m);
	return c < 0 ? -1 : powMod(g, c, m);
}
