using path = pair<ll, int>; //dist, destination

void dijkstra(const vector<vector<path>> &adjlist, int start) {
	priority_queue<path, vector<path>, greater<path>> pq;
	vector<ll> dist(sz(adjlist), INF);
	vector<int> prev(sz(adjlist), -1);
	dist[start] = 0; pq.emplace(0, start);

	while (!pq.empty()) {
		auto [dc, c] = pq.top(); pq.pop();
		if (dc > dist[c]) continue; // WICHTIG!

		for (auto [dx, x] : adjlist[c]) {
			ll newDist = dc + dx;
			if (newDist < dist[x]) {
				dist[x] = newDist;
				prev[x] = c;
				pq.emplace(newDist, x);
	}}}
	//return dist, prev;
}
