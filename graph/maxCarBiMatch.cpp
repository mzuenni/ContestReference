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

int kuhn(int n) { // n = #Knoten links.
	pairs.assign(sz(adj), -1);
	int ans = 0;
	// Greedy Matching. Optionale Beschleunigung.
	for (int v = 0; v < l; v++) for (int u : adj[v])
		if (pairs[u] < 0) {pairs[u] = v; pairs[v] = u; ans++; break;}
	for (int v = 0; v < n; v++) if (pairs[v] < 0) {
		visited.assign(n, false);
		ans += dfs(v);
	}
	return ans; // Größe des Matchings.
}
