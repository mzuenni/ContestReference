vector<vector<int>> havelHakimi(const vector<int>& deg) {
	priority_queue<pair<int, int>> pq;
	for (int i = 0; i < sz(deg); i++) {
		if (deg[i] > 0) pq.push({deg[i], i});
	}
	vector<vector<int>> adj;
	while (!pq.empty()) {
		auto [degV, v] = pq.top(); pq.pop();
		if (sz(pq) < degV) return {}; //impossible
		vector<pair<int, int>> todo(degV);
		for (auto& e : todo) e = pq.top(), pq.pop();
		for (auto [degU, u] : todo) {
			adj[v].push_back(u);
			adj[u].push_back(v);
			if (degU > 1) pq.push({degU - 1, u});
	}}
	return adj;
}
