void fft(vector<ll>& a, bool inv = false) {
	int n = sz(a);
	for (int s = 1; s < n; s *= 2) {
		for (int i = 0; i < n; i += 2 * s) {
			for (int j = i; j < i + s; j++) {
				ll& u = a[j], &v = a[j + s];
				tie(u, v) = inv ? pair(v, u - v) : pair(u + v, u);
}}}}
