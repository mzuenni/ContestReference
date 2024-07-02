vector<vector<ll>> dp;
vector<vector<ll>> C;

void rec(int i, int j0, int j1, int k0, int k1) {
	if (j1 < j0) return;
	int jmid = (j0 + j1) / 2;

	dp[i][jmid] = inf;
	int bestk = k0;
	for (int k = k0; k < min(jmid, k1 + 1); ++k) {
		if (dp[i - 1][k] + C[k + 1][jmid] < dp[i][jmid]) {
			dp[i][jmid] = dp[i - 1][k] + C[k + 1][jmid];
			bestk = k;
	}}

	rec(i, j0, jmid - 1, k0, bestk);
	rec(i, jmid + 1, j1, bestk, k1);
}

ll calc(int n, int k) {
	dp = vector<vector<ll>>(k, vector<ll>(n, inf));
	for (int i = 0; i < n; i++) dp[0][i] = C[0][i];
	for (int i = 1; i < k; i++) {
		rec(i, 0, n - 1, 0, n - 1);
	}
	return dp[k - 1][n - 1];
}
