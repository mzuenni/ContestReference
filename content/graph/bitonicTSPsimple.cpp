vector<vector<double>> dist; // Entfernungen zwischen Punkten.
vector<vector<double>> dp;

double get(int p1, int p2) {
	int v = max(p1, p2) + 1;
	if (v == sz(dist)) return dist[p1][v - 1] + dist[p2][v - 1];
	if (dp[p1][p2] >= 0.0) return dp[p1][p2];
	double tryLR = dist[p1][v] + get(v, p2);
	double tryRL = dist[p2][v] + get(p1, v);
	return dp[p1][p2] = min(tryLR, tryRL);
}

auto bitonicTSP() {
	dp = vector<vector<double>>(sz(dist),
	            vector<double>(sz(dist), -1));
	get(0, 0);
	// return dp[0][0]; // Länger der Tour
	vector<int> lr = {0}, rl = {0};
	for (int p1 = 0, p2 = 0, v; (v = max(p1, p2)+1) < sz(dist);) {
		if (dp[p1][p2] == dist[p1][v] + dp[v][p2]) {
			lr.push_back(v); p1 = v;
		} else {
			rl.push_back(v); p2 = v;
	}}
	lr.insert(lr.end(), rl.rbegin(), rl.rend());
	return lr;// Enthält Knoten 0 zweimal. An erster und letzter Position.
}
