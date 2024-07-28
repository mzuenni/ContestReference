ll rec(vector<pt>::iterator a, int l, int r) {
	if (r - l < 2) return INF;
	int m = (l + r) / 2;
	ll midx = a[m].real();
	ll ans = min(rec(a, l, m), rec(a, m, r));

	inplace_merge(a+l, a+m, a+r, [](const pt& x, const pt& y) {
		return x.imag() < y.imag();
	});

	pt tmp[8];
	fill(all(tmp), a[l]);
	for (int i = l + 1, next = 0; i < r; i++) {
		if (ll x = a[i].real() - midx; x * x < ans) {
			for (pt& p : tmp) ans = min(ans, norm(p - a[i]));
			tmp[next++ & 7] = a[i];
		}
	}
	return ans;
}

ll shortestDist(vector<pt> a) { // sz(pts) > 1
	sort(all(a), [](const pt& x, const pt& y) {
		return x.real() < y.real();
	});
	return rec(a.begin(), 0, sz(a));
}
