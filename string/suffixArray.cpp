struct SuffixArray {
	int n;
	vector<int> SA, LCP;
	vector<vector<int>> P;

	SuffixArray(const string& s) : n(sz(s)), SA(n), LCP(n) {
		vector<ll> L(n);
		P.assign(__lg(n - 1) + 2, vector<int>(n, 1));
		P[0] = vector<int>(all(s));
		iota(all(SA), 0);
		for (int k = 1, c = 1; c < n; k++, c *= 2) {
			for (int i = 0; i < n; i++) L[i] = (ll)P[k - 1][i] << 32;
			for (int i = 0; i+c < n; i++) L[i] |= P[k - 1][i + c];
			sort(all(SA), [&](int a, int b) {return L[a] < L[b];});
			for (int i = 1; i < n; i++) {
				P[k][SA[i]] = P[k][SA[i-1]] + (L[SA[i]] != L[SA[i-1]]);
		}}
		for (int i = 1; i < n; i++) LCP[i] = lcp(SA[i-1], SA[i]);
	}

	// x and y are text-indices, not SA-indices.
	int lcp(int x, int y) {
		int ret = 0;
		if (x == y) return n - x;
		for (int i = sz(P) - 1; i >= 0 && max(x, y) + ret < n; i--) {
			if (P[i][x + ret] == P[i][y + ret]) ret += 1 << i;
		}
		return ret;
	}
};
