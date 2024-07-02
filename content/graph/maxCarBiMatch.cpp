vector<vector<int>> adj;
vector<int> pairs; // Der gematchte Knoten oder -1.
vector<bool> visited;

bool dfs(int v) {
	if (visited[v]) return false;
	visited[v] = true;
	for (int u : adj[v]) if (pairs[u] < 0 || dfs(pairs[u])) {
		pairs[u] = v; pairs[v] = u; return true;
	}
	return false;
}

int kuhn(int l) { // l = #Knoten links.
	pairs.assign(sz(adj), -1);
	int ans = 0;
	// Greedy Matching. Optionale Beschleunigung.
	for (int v = 0; v < l; v++) for (int u : adj[v])
		if (pairs[u] < 0) {pairs[u] = v; pairs[v] = u; ans++; break;}
	for (int v = 0; v < l; v++) if (pairs[v] < 0) {
		visited.assign(l, false);
		ans += dfs(v);
	}
	return ans; // Größe des Matchings.
}
