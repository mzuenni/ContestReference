int fastSubsetSum(vector<int> w, int t){
	int a = 0, b = 0;
	while(b < sz(w) && a + w[b] <= t) a += w[b++];
	if(b == sz(w)) return a;
	int m = *max_element(all(w));
	vector<int> dp(2*m, -1), old;
	dp[m+a-t] = b;
	for(int i = b; i < sz(w); i++){
		old = dp;
		for(int j = 0; j < m; j++){
			dp[j+w[i]] = max(dp[j+w[i]], old[j]);
		}
		for(int j = 2*m-1; j > m; j--){
			for(int k = max(old[j], 0); k < dp[j]; k++){
				dp[j-w[k]] = max(dp[j-w[k]], k);
			}
		}
	}
	for(a = t; dp[m+a-t] < 0; a--);
	return a;
}