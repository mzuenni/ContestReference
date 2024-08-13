vector<vector<double>> dist; // Initialisiere mit Entfernungen zwischen Punkten.

auto bitonicTSP() {
	vector<double> dp(sz(dist), HUGE_VAL);
	vector<int> pre(sz(dist)); // nur für Tour
	dp[0] = 0; dp[1] = 2 * dist[0][1]; pre[1] = 0;
	for (unsigned int i = 2; i < sz(dist); i++) {
		double link = 0;
		for (int j = i - 2; j >= 0; j--) {
			link += dist[j + 1][j + 2];
			double opt = link + dist[j][i] + dp[j + 1] - dist[j][j + 1];
			if (opt < dp[i]) {
				dp[i] = opt;
				pre[i] = j;
	}}}
	// return dp.back(); // Länger der Tour

	int j, n = sz(dist) - 1;
	vector<int> ut, lt = {n, n - 1};
	do {
		j = pre[n];
		(lt.back() == n ? lt : ut).push_back(j);
		for (int i = n - 1; i > j + 1; i--) {
			(lt.back() == i ? lt : ut).push_back(i - 1);
		}
	} while(n = j + 1, j > 0);
	(lt.back() == 1 ? lt : ut).push_back(0);
	reverse(all(lt));
	lt.insert(lt.end(), all(ut));
	return lt; // Enthält Knoten 0 zweimal. An erster und letzter Position.
}
