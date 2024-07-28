vector<ll> mul(vector<ll> a, vector<ll> b) {
	int n = 1 << (__lg(sz(a) + sz(b) - 1) + 1);
	a.resize(n), b.resize(n);
	ntt(a), ntt(b);
	for (int i=0; i<n; i++) a[i] = a[i] * b[i] % mod;
	ntt(a, true);
	return a;
}
