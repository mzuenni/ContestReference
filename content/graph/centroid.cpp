vector<int> s;
void dfs_sz(int v, int from = -1) {
	s[v] = 1;
	for (int u : adj[v]) if (u != from) {
		dfs_sz(u, v);
		s[v] += s[u];
}}

pair<int, int> dfs_cent(int v, int from, int n) {
	for (int u : adj[v]) if (u != from) {
		if (2 * s[u] == n) return {v, u};
		if (2 * s[u] > n) return dfs_cent(u, v, n);
	}
	return {v, -1};
}

pair<int, int> find_centroid(int root = 0) {
	s.resize(sz(adj));
	dfs_sz(root);
	return dfs_cent(root, -1, s[root]);
}
