vector<pair<int, int>> antipodalPoints(vector<pt>& h) {
	if (sz(h) < 2) return {};
	vector<pair<int, int>> result;
	for (int i = 0, j = 1; i < j; i++) {
		while (true) {
			result.push_back({i, j});
			if (cross(h[(i + 1) % sz(h)] - h[i],
			          h[(j + 1) % sz(h)] - h[j]) <= 0) break;
			j = (j + 1) % sz(h);
	}}
	return result;
}
