ll inversions(const vector<ll>& v) {
	Tree<pair<ll, ll>> t; //ordered statistics tree @\sourceref{datastructures/pbds.cpp}@
	ll res = 0;
	for (ll i = 0; i < sz(v); i++) {
		res += i - t.order_of_key({v[i], i});
		t.insert({v[i], i});
	}
	return res;
}
