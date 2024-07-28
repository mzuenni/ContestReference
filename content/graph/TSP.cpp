vector<vector<ll>> dist; // Entfernung zwischen je zwei Punkten.

auto TSP() {
	int n = sz(dist), m = 1 << n;
	vector<vector<edge>> dp(n, vector<edge>(m, edge{INF, -1}));

	for (int c = 0; c < n; c++)
		dp[c][m-1].dist = dist[c][0], dp[c][m-1].to = 0;

	for (int v = m - 2; v >= 0; v--) {
		for (int c = n - 1; c >= 0; c--) {
			for (int g = 0; g < n; g++) {
				if (g != c && !((1 << g) & v)) {
					if ((dp[g][(v | (1 << g))].dist + dist[c][g]) <
					    dp[c][v].dist) {
						dp[c][v].dist =
							dp[g][(v | (1 << g))].dist + dist[c][g];
						dp[c][v].to = g;
	}}}}}
	// return dp[0][1]; // Länge der Tour

	vector<int> tour = {0};
	int v = 0;
	while (tour.back() != 0 || sz(tour) == 1)
		tour.push_back(dp[tour.back()]
		                 [(v |= (1 << tour.back()))].to);
	// Enthält Knoten 0 zweimal. An erster und letzter Position.
	return tour;
}
