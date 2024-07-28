ll dlog(ll a, ll b, ll m) { //a > 0!
	ll bound = sqrtl(m) + 1; //memory usage bound < p
	vector<pair<ll, ll>> vals(bound);
	for (ll i = 0, e = 1; i < bound; i++, e = (e * a) % m) {
		vals[i] = {e, i};
	}
	vals.emplace_back(m, 0);
	sort(all(vals));
	ll fact = powMod(a, m - bound - 1, m);

	for (ll i = 0; i < m; i += bound, b = (b * fact) % m) {
		auto it = lower_bound(all(vals), pair<ll, ll>{b, 0});
		if (it->first == b) {
			return (i + it->second) % m;
	}}
	return -1;
}
