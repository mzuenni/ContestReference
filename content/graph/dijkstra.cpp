using path = pair<ll, int>; //dist, destination

auto dijkstra(const vector<vector<path>>& adj, int start) {
	priority_queue<path, vector<path>, greater<path>> pq;
	vector<ll> dist(sz(adj), INF);
	vector<int> prev(sz(adj), -1);
	dist[start] = 0; pq.emplace(0, start);

	while (!pq.empty()) {
		auto [dv, v] = pq.top(); pq.pop();
		if (dv > dist[v]) continue; // WICHTIG!

		for (auto [du, u] : adj[v]) {
			ll newDist = dv + du;
			if (newDist < dist[u]) {
				dist[u] = newDist;
				prev[u] = v;
				pq.emplace(dist[u], u);
	}}}
	return dist; //return prev;
}
