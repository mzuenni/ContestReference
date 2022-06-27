vector<int> Z(const vector<int> &s) {
	int n = sz(s);
	vector<int> z(n, n);
	int l = 0, r = 0, p, q;
	for (int i = 1; i < n; ++i) {
		if (i <= r && z[i - l] < r - i + 1) {
			z[i] = z[i - l];
		} else {
			if (i > r) p = 0, q = i;
			else p = r - i + 1, q = r + 1;
			while (q < n && s[p] == s[q]) ++p, ++q;
			z[i] = q - i, l = i, r = q - 1;
	}}
	return z;
}
