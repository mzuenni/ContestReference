vector<vector<ll>> dp;
vector<vector<ll>> C;

void rec(int i, int j0, int j1, int m0, int m1) {
	if (j1 < j0) return;
	int jmid = (j0 + j1) / 2;

	dp[i][jmid] = INF;
	int bestk = m0;
	for (int k = m0; k < min(jmid, m1 + 1); ++k) {
		if (dp[i - 1][k] + C[k + 1][jmid] < dp[i][jmid]) {
			dp[i][jmid] = dp[i - 1][k] + C[k + 1][jmid];
			bestk = k;
	}}

	rec(i, j0, jmid - 1, m0, bestk);
	rec(i, jmid + 1, j1, bestk, m1);
}

ll calc(int n, int m) {
	dp = vector<vector<ll>>(m, vector<ll>(n, INF));
	for (int i = 0; i < n; i++) dp[0][i] = C[0][i];
	for (int i = 1; i < m; i++) {
		rec(i, 0, n - 1, 0, n - 1);
	}
	return dp[m - 1][n - 1];
}
