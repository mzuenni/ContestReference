ll dlog(ll a, ll b, ll m) { //a > 0!
	ll bound = sqrtl(m) + 1; //memory usage bound
	map<ll, ll> vals;
	for (ll i = 0, e = 1; i < bound; i++, e = (e * a) % m) {
		vals[e] = i;
	}
	ll fact = powMod(a, m - bound - 1, m);

	for (ll i = 0; i < m; i += bound, b = (b * fact) % m) {
		if (vals.count(b)) {
			return i + vals[b];
	}}
	return -1;
}
