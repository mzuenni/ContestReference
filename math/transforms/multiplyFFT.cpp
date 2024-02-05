vector<ll> mul(vector<ll>& a, vector<ll>& b) {
	int n = 1 << (__lg(sz(a) + sz(b) - 1) + 1);
	vector<cplx> a2(all(a)), b2(all(b));
	a2.resize(n), b2.resize(n);
	fft(a2), fft(b2);
	for (int i=0; i<n; i++) a2[i] *= b2[i];
	fft(a2, true);

	vector<ll> ans(n);
	for (int i=0; i<n; i++) ans[i] = llround(a2[i].real());
	return ans;
}
