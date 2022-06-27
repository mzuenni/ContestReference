vector<vector<int>> havelHakimi(const vector<int>& deg) {
	priority_queue<pair<int, int>> pq;
	for (int i = 0; i < sz(deg); i++) pq.push({deg[i], i});
	vector<vector<int>> adj;
	while (!pq.empty()) {
		auto v = pq.top(); pq.pop();
		if (sz(pq) < v.first) return {}; //ERROR
		vector<pair<int, int>> todo;
		for (int i = 0; i < v.first; i++) {
			auto u = pq.top(); pq.pop();
			adj[v.second].push_back(u.second);
			adj[u.second].push_back(v.second);
			u.first--;
			if (u.first > 0) todo.push_back(u);
		}
		for (auto e : todo) pq.push(e);
	}
	return adj;
} 
