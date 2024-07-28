vector<vector<int>> adj;
map<vector<int>, int> known; // dont reset!

int treeLabel(int v, int from = -1) {
	vector<int> children;
	for (int u : adj[v]) {
		if (u == from) continue;
		children.push_back(treeLabel(u, v));
	}
	sort(all(children));
	if (known.find(children) == known.end()) {
		known[children] = sz(known);
	}
	return known[children];
}
