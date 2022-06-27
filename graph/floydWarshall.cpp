vector<vector<ll>> dist; // Entfernung zwischen je zwei Punkten.
vector<vector<int>> pre;

void floydWarshall() {
	pre.assign(sz(dist), vector<int>(sz(dist), -1));
	for (int i = 0; i < sz(dist); i++) {
		for (int j = 0; j < sz(dist); j++) {
			if (dist[i][j] < INF) {
				pre[i][j] = j;
	}}}

	for (int k = 0; k < sz(dist); k++) {
		for (int i = 0; i < sz(dist); i++) {
			for (int j = 0; j < sz(dist); j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					pre[i][j] = pre[i][k];
}}}}}

vector<int> getPath(int u, int v) {
	//return dist[u][v]; // Pfadlänge u -> v
	if (pre[u][v] < 0) return {};
	vector<int> path = {v};
	while (u != v) path.push_back(u = pre[u][v]);
	return path; //Pfad u -> v
}
