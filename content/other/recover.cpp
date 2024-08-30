ll sq(ll x) {return x*x;}

array<ll, 2> recover(ll c, ll m) {
	array<ll, 2> u = {m, 0}, v = {c, 1};
	while (m <= 2 * sq(v[0])) {
		ll q = u[0] / v[0];
		u[0] -= q * v[0];
		u[1] -= q * v[1];
		swap(u, v);
	}
	if (v[1] <= 0 || 2 * sq(v[1]) >= m) return {-1, -1};
	return v;
}
