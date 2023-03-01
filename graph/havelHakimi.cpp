vector<vector<int>> havelHakimi(const vector<int>& deg) {
	priority_queue<pair<int, int>> pq;
	for (int i = 0; i < sz(deg); i++) pq.push({deg[i], i});
	vector<vector<int>> adj;
	while (!pq.empty()) {
		auto [degV, v] = pq.top(); pq.pop();
		if (sz(pq) < degV) return {}; //impossible
		vector<pair<int, int>> todo;
		for (int i = 0; i < degV; i++) {
			auto [degU, v] = pq.top(); pq.pop();
			adj[v].push_back(u);
			adj[u].push_back(v);
			if (degU > 1) todo.push_back({degU - 1, u});
		}
		for (auto e : todo) pq.push(e);
	}
	return adj;
}
