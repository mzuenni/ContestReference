void bitwiseConv(vector<ll>& a, bool inv = false) {
	int n = sz(a);
	for (int s = 1; s < n; s *= 2) {
		for (int i = 0; i < n; i += 2 * s) {
			for (int j = i; j < i + s; j++) {
				ll& u = a[j], &v = a[j + s];
				tie(u, v) = inv ? pair(v - u, u) : pair(v, u + v); // AND
				//tie(u, v) = inv ? pair(v, u - v) : pair(u + v, u); //OR
				//tie(u, v) = pair(u + v, u - v); // XOR
	}}}
	//if (inv) for (ll& x : a) x /= n; // XOR (careful with MOD)
}
