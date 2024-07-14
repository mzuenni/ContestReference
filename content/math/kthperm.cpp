vector<ll> kthperm(ll n, ll k) {
	Tree<ll> t;
	vector<ll> res(n);
	for (ll i = 1; i <= n; k /= i, i++) {
		t.insert(i - 1);
		res[n - i] = k % i;
	}
	for (ll& x : res) {
		auto it = t.find_by_order(x);
		x = *it;
		t.erase(it);
	}
	return res;
}
