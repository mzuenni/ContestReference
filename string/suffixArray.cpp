struct SuffixArray {
	int n, k, c;
	vector<int> SA, LCP;
	vector<vector<int>> P;

	SuffixArray(const string& s) : n(sz(s)), SA(n), LCP(n) {
		vector<ll> L(n);
		P.assign(__lg(n)+2, vector<int>(n));
		for (int i = 0; i < n; i++) P[0][i] = s[i];
		iota(all(SA), 0);
		for (k = 1, c = 1; c < n; k++, c *= 2) {
			for (int i = 0; i < n; i++) L[i] = (ll)P[k-1][i] << 32;
			for (int i = 0; i+c < n; i++) L[i] |= P[k-1][i+c];
			sort(all(SA), [&](int a, int b){
				return L[a] != L[b] ? L[a] < L[b] : a < b;
			});
			P[k][SA[0]] = 1;
			for (int i = 1; i < n; i++) {
				P[k][SA[i]] = L[SA[i]] == L[SA[i-1]] ? P[k][SA[i-1]]
				                                     : i+1;
		}}
		for (int i = 1; i < n; i++) LCP[i] = lcp(SA[i-1], SA[i]);
	}

	// x and y are text-indices, not SA-indices.
	int lcp(int x, int y) {
		int ret = 0;
		if (x == y) return n - x;
		for (int i = k - 1; i >= 0 && x < n && y < n; i--) {
			if (P[i][x] == P[i][y]) {
				x += 1 << i;
				y += 1 << i;
				ret += 1 << i;
		}}
		return ret;
	}
};
