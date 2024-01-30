vector<int> lis(vector<ll>& a) {
	int n = sz(a), len = 0;
	vector<ll> dp(n, INF), dp_id(n), prev(n);
	for (int i = 0; i < n; i++) {
		int pos = lower_bound(all(dp), a[i]) - dp.begin();
		dp[pos] = a[i];
		dp_id[pos] = i;
		prev[i] = pos ? dp_id[pos - 1] : -1;
		len = max(len, pos + 1);
	}
	// reconstruction
	vector<int> res(len);
	for (int x = dp_id[len-1]; len--; x = prev[x]) {
		res[len] = x;
	}
	return res; // indices of one LIS
}
