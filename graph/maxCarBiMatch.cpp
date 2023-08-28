vector<vector<int>> adj;
vector<int> pairs; // Der gematchte Knoten oder -1.
vector<bool> visited;

bool dfs(int v) {
	if (visited[v]) return false;
	visited[v] = true;
	for (auto w : adj[v]) if (pairs[w] < 0 || dfs(pairs[w])) {
		pairs[w] = v; pairs[v] = w; return true;
	}
	return false;
}

int kuhn(int n) { // n = #Knoten links.
	pairs.assign(sz(adj), -1);
	int ans = 0;
	// Greedy Matching. Optionale Beschleunigung.
	for (int i = 0; i < n; i++) for (auto w : adj[i])
		if (pairs[w] < 0) {pairs[i] = w; pairs[w] = i; ans++; break;}
	for (int i = 0; i < n; i++) if (pairs[i] < 0) {
		visited.assign(n, false);
		ans += dfs(i);
	}
	return ans; // Größe des Matchings.
}
