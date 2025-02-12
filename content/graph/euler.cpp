vector<vector<pair<int, int>>> adj; // gets destroyed!
vector<int> cycle;

void addEdge(int u, int v) {
	adj[u].emplace_back(v, sz(adj[v]));
	adj[v].emplace_back(u, sz(adj[u]) - 1); // remove for directed
}

void euler(int v) {
	while (!adj[v].empty()) {
		auto [u, rev] = adj[v].back();
		adj[v].pop_back();
		if (u < 0) continue; // remove for directed
		adj[u][rev].first = -1; // remove for directed
		euler(u);
	}
	cycle.push_back(v); // Zyklus in umgekehrter Reihenfolge.
}
