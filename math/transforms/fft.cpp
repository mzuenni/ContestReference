using cplx = complex<double>; // Eigene Implementierung ist schneller.

void fft(vector<cplx>& a, bool inverse = 0) {
	int n = sz(a);
	for (int i = 0, j = 1; j < n - 1; ++j) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	for (int s = 1; s < n; s *= 2) {
		double angle = PI / s * (inverse ? -1 : 1);
		cplx ws(cos(angle), sin(angle));
		for (int j = 0; j < n; j+= 2 * s) {
			cplx w = 1;
			for (int k = 0; k < s; k++) {
				cplx u = a[j + k], t = a[j + s + k] * w;
				a[j + k] = u + t;
				a[j + s + k] = u - t;
				if (inverse) a[j + k] /= 2, a[j + s + k] /= 2;
				w *= ws;
}}}}
