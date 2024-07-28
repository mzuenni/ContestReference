vector<int> manacher(const string& t) {
	//transforms "aa" to ".a.a." to find even length palindromes
	string s(sz(t) * 2 + 1, '.');
	for (int i = 0; i < sz(t); i++) s[2 * i + 1] = t[i];

	int mid = 0, r = 0, n = sz(s);
	vector<int> pal(n);
	for (int i = 1; i < n - 1; i++) {
		if (r > i) pal[i] = min(r - i, pal[2 * mid - i]);
		while (pal[i] < min(i, n - i - 1) &&
		       s[i + pal[i] + 1] == s[i - pal[i] - 1]) {
			pal[i]++;
		}
		if (i + pal[i] > r) mid = i, r = i + pal[i];
	}

	//convert lengths to constructed string s (optional)
	//for (int i = 0; i < n; i++) pal[i] = 2 * pal[i] + 1;
	return pal;
}
