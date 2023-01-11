vector<cplx> mul(vector<cplx>& a, vector<cplx>& b) {
	vector<cplx> c(sz(a)), d(sz(a));
	for (int i = 0; i < sz(b); i++) {
		c[i] = {real(a[i]), real(b[i])};
	}
	c = fft(c);
	for (int i = 0; i < sz(b); i++) {
		int j = (sz(a) - i) % sz(a);
		cplx x = (c[i] + conj(c[j])) / cplx{2, 0}; //fft(a)[i];
		cplx y = (c[i] - conj(c[j])) / cplx{0, 2}; //fft(b)[i];
		d[i] = x * y;
	}		
	return fft(d, true);
} 
