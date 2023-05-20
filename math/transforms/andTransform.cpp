void fft(vector<cplx>& a, bool inverse = 0) {
	int n = sz(a);
	for (int i = 0, j = 1; j < n - 1; ++j) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	for (int s = 1; s < n; s *= 2) {
		for (int j = 0; j < n; j+= 2 * s) {
			for (int k = 0; k < s; k++) {
				ll u = a[j + k], t = a[j + s + k];
				if (!inverse) {
					a[j + k] = t;
					a[j + s + k] = u + t;
				} else {
					a[j + k] = t - u;
					a[j + s + k] = u;
}}}}}
