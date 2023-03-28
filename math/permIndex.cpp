ll permIndex(vector<ll> v) {
	Tree<ll> t;
	reverse(all(v));
	for (ll& x : v) {
		t.insert(x);
		x = t.order_of_key(x);
	}
	ll res = 0;
	for (int i = sz(v); i > 0; i--) {
		res = res * i + v[i - 1];
	}
	return res;
}
