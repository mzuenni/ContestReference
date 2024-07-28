ll calc(int n, int m, const vector<vector<ll>>& C) {
	vector<vector<ll>> dp(m, vector<ll>(n, inf));
	vector<vector<int>> opt(m, vector<int>(n + 1, n - 1));

	for (int i = 0; i < n; i++) dp[0][i] = C[0][i];
	for (int i = 1; i < m; i++) {
		for (int j = n - 1; j >= 0; --j) {
			opt[i][j] = i == 1 ? 0 : opt[i - 1][j];
			for (int k = opt[i][j]; k <= min(opt[i][j+1], j-1); k++) {
				if (dp[i][j] <= dp[i - 1][k] + C[k + 1][j]) continue;
				dp[i][j] = dp[i - 1][k] + C[k + 1][j];
				opt[i][j] = k;
	}}}
	return dp[m - 1][n - 1];
}
