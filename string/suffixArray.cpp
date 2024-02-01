struct SuffixArray {
	int n, s, c;
	vector<int> SA, LCP;
	vector<vector<int>> P;
	vector<ll> L;

	SuffixArray(const string& s) : n(sz(s)), SA(n), LCP(n), L(n) {
		P.assign(__lg(n)+2, vector<int>(n));
		for (int i = 0; i < n; i++) P[0][i] = s[i];
		iota(all(SA), 0);
		for (s = 1, c = 1; c < n; s++, c *= 2) {
			for (int i = 0; i < n; i++) L[i] = (ll)P[s-1][i] << 32;
			for (int i = 0; i+c < n; i++) L[i] |= P[s-1][i+c];
			sort(all(SA), [&](int a, int b){
				return L[a] != L[b] ? L[a] < L[b] : a < b;
			});
			P[s][SA[0]] = 1;
			for (int i = 1; i < n; i++) {
				P[s][SA[i]] = L[SA[i]] == L[SA[i-1]] ? P[s][SA[i-1]]
				                                     : i+1;
		}}
		for (int i = 1; i < n; i++) LCP[i] = lcp(SA[i-1], SA[i]);
	}

	// x and y are text-indices, not SA-indices.
	int lcp(int x, int y) {
		int ret = 0;
		if (x == y) return n - x;
		for (int k = s - 1; k >= 0 && x < n && y < n; k--) {
			if (P[k][x] == P[k][y]) {
				x += 1 << k;
				y += 1 << k;
				ret += 1 << k;
		}}
		return ret;
	}
};
