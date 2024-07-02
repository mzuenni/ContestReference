double costs[N_LEFT][N_RIGHT];

// Es muss l<=r sein! (sonst Endlosschleife)
double match(int l, int r) {
	vector<double> lx(l), ly(r);
	//xy is matching from l->r, yx from r->l, or -1
	vector<int> xy(l, -1), yx(r, -1);
	vector<pair<double, int>> slack(r);

	for (int x = 0; x < l; x++)
		lx[x] = *max_element(costs[x], costs[x] + r);
	for (int root = 0; root < l; root++) {
		vector<int> aug(r, -1);
		vector<bool> s(l);
		s[root] = true;
		for (int y = 0; y < r; y++) {
			slack[y] = {lx[root] + ly[y] - costs[root][y], root};
		}
		int y = -1;
		while (true) {
			double delta = INF;
			int x = -1;
			for (int yy = 0; yy < r; yy++) {
				if (aug[yy] < 0 && slack[yy].first < delta) {
					tie(delta, x) = slack[yy];
					y = yy;
			}}
			if (delta > 0) {
				for (int x = 0; x < l; x++) if (s[x]) lx[x] -= delta;
				for (int y = 0; y < r; y++) {
					if (aug[y] >= 0) ly[y] += delta;
					else slack[y].first -= delta;
			}}
			aug[y] = x;
			x = yx[y];
			if (x < 0) break;
			s[x] = true;
			for (int y = 0; y < r; y++) {
				if (aug[y] < 0) {
					double alt = lx[x] + ly[y] - costs[x][y];
					if (slack[y].first > alt) {
						slack[y] = {alt, x};
		}}}}
		while (y >= 0) {
			yx[y] = aug[y];
			swap(y, xy[aug[y]]);
	}}
	return accumulate(all(lx), 0.0) +
	       accumulate(all(ly), 0.0); // Wert des Matchings
}
