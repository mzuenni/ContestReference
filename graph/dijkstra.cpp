using path = pair<ll, int>; //dist, destination

void dijkstra(const vector<vector<path>> &adjlist, int start) {
	priority_queue<path, vector<path>, greater<path>> pq;
	vector<ll> dist(sz(adjlist), INF);
	vector<int> prev(sz(adjlist), -1);
	dist[start] = 0; pq.emplace(0, start);

	while (!pq.empty()) {
		path front = pq.top(); pq.pop();
		if (front.first > dist[front.second]) continue; // WICHTIG!

		for (path e : adjlist[front.second]) {
			ll newDist = front.first + e.first;
			if (newDist < dist[e.second]) {
				dist[e.second] = newDist;
				prev[e.second] = front.second;
				pq.emplace(newDist, e.second);
	}}}
	//return dist, prev;
}
