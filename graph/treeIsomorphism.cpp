vector<vector<int>> adj;
map<vector<int>, int> known;

int treeLabel(int root, int p = -1) {
	vector<int> children;
	for (int x : adj[root]) {
		if (x == p) continue;
		children.push_back(treeLabel(x, root));
	}
	sort(all(children));
	if (known.find(children) == known.end()) {
		known[children] = sz(known);
	}
	return known[children];
}
