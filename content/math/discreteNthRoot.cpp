ll root(ll a, ll b, ll m) {
	ll g = findPrimitive(m);
	ll c = dlog(powMod(g, a, m), b, m); //dLog @\sourceref{math/discreteLogarithm.cpp}@
	return c < 0 ? -1 : powMod(g, c, m);
}
