vector<ll> mul(vector<ll> a, vector<ll> b) {
	int n = 1 << (__lg(max(sz(a), sz(b)) - 1) + 1);
	if (sz(a) == 1 && sz(b) == 1) n = 1;
	a.resize(n), b.resize(n);
	bitwiseConv(a), bitwiseConv(b);
	for (int i=0; i<n; i++) a[i] *= b[i]; // MOD?
	bitwiseConv(a, true);
	return a;
}
