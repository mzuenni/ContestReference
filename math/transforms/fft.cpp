using cplx = complex<double>;

void fft(vector<cplx>& a, bool inv = false) {
	int n = sz(a);
	for (int i = 0, j = 1; j < n - 1; ++j) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	static vector<cplx> ws(2, 1);
	for (static int k = 2; k < n; k *= 2) {
		ws.resize(n);
		cplx w = polar(1.0, acos(-1.0) / k);
		for (int i=k; i<2*k; i++) ws[i] = ws[i/2] * (i % 2 ? w : 1);
	}
	for (int s = 1; s < n; s *= 2) {
		for (int j = 0; j < n; j += 2 * s) {
			for (int k = 0; k < s; k++) {
				cplx u = a[j + k], t = a[j + s + k];
				t *= (inv ? conj(ws[s + k]) : ws[s + k]);
				a[j + k] = u + t;
				a[j + s + k] = u - t;
				if (inv) a[j + k] /= 2, a[j + s + k] /= 2;
}}}}
