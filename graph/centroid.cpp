vector<int> s;
void dfs1(int u, int v = -1) {
	s[u] = 1;
	for (int w : adj[u]) {
		if (w == v) continue;
		dfs1(w, u);
		s[u] += s[w];
}}

pair<int, int> dfs2(int u, int v, int n) {
	for (int w : adj[u]) {
		if (2 * s[w] == n) return {u, w};
		if (w != v && 2 * s[w] > n) return dfs2(w, u, n);
	}
	return {u, -1};
}

pair<int, int> find_centroid(int root) {
	// s muss nicht initialisiert werden, nur groß genug sein
	dfs1(root);
	return dfs2(root, -1, s[root]);
}
