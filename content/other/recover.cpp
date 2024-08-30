ll sq(ll x) {return x*x;}

pair<ll, ll> recover(ll c, ll m) {
	array<ll, 3> u = {1, 0, m}, v = {0, 1, c};
	while (m <= 2 * sq(v[2])) {
		ll q = u[2] / v[2];
		for (int i : {0, 1, 2}) u[i] -= q * v[i];
		swap(u, v);
	}
	if (v[1] < 0 || 2 * sq(v[1]) >= m) return {-1, -1};
	return {v[2], v[1]};
}
