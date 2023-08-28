constexpr int MOD=1'000'000'007, I=10;
vector<vector<ll>> adj, mat;

int max_matching() {
	int ans = 0;
	mat.assign(sz(adj), {});
	for (int _ = 0; _ < I; _++) {
		for (int i = 0; i < sz(adj); i++) {
			mat[i].assign(sz(adj), 0);
			for (int j : adj[i]) {
				if (j < i) {
					mat[i][j] = rand() % (MOD - 1) + 1;
					mat[j][i] = MOD - mat[i][j];
		}}}
		gauss(sz(adj), MOD); //LGS unten
		int rank = 0;
		for (auto& row : mat) {
			if (*min_element(all(row)) != 0) rank++;
		}
		ans = max(ans, rank / 2);
	}
	return ans;
}
