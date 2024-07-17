vector<vector<ll>> dist; // Entfernung zwischen je zwei Punkten.
vector<vector<int>> next;

void floydWarshall() {
	next.assign(sz(dist), vector<int>(sz(dist), -1));
	for (int i = 0; i < sz(dist); i++) {
		for (int j = 0; j < sz(dist); j++) {
			if (dist[i][j] < INF) {
				next[i][j] = j;
	}}}

	for (int k = 0; k < sz(dist); k++) {
		for (int i = 0; i < sz(dist); i++) {
			for (int j = 0; j < sz(dist); j++) {
				// only needed if dist can be negative
				if (dist[i][k] == INF || dist[k][j] == INF) continue;
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					next[i][j] = next[i][k];
}}}}}

vector<int> getPath(int u, int v) {
	if (next[u][v] < 0) return {};
	vector<int> path = {u};
	while (u != v) path.push_back(u = next[u][v]);
	return path; //Pfad u -> v
}
