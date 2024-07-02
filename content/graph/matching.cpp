constexpr int MOD=1'000'000'007, I=10;
vector<vector<ll>> adj, mat;

int max_matching() {
	int ans = 0;
	mat.assign(sz(adj), {});
	for (int _ = 0; _ < I; _++) {
		for (int v = 0; v < sz(adj); v++) {
			mat[v].assign(sz(adj), 0);
			for (int u : adj[v]) {
				if (u < v) {
					mat[v][u] = rand() % (MOD - 1) + 1;
					mat[u][v] = MOD - mat[v][u];
		}}}
		gauss(sz(adj), MOD); //LGS @\sourceref{math/lgsFp.cpp}@
		int rank = 0;
		for (auto& row : mat) {
			if (*min_element(all(row)) != 0) rank++;
		}
		ans = max(ans, rank / 2);
	}
	return ans;
}
