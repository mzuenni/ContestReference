void bellmannFord(int n, vector<edge> edges, int start) {
	vector<ll> dist(n, INF), parent(n, -1);
	dist[start] = 0;

	for (int i = 1; i < n; i++) {
		for (edge& e : edges) {
			if (dist[e.from] != INF &&
			    dist[e.from] + e.cost < dist[e.to]) {
				dist[e.to] = dist[e.from] + e.cost;
				parent[e.to] = e.from;
	}}}

	for (edge& e : edges) {
		if (dist[e.from] != INF &&
		    dist[e.from] + e.cost < dist[e.to]) {
			// Negativer Kreis gefunden.
}}} //return dist, parent?;
