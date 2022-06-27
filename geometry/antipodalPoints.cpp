vector<pair<int, int>> antipodalPoints(vector<pt>& h) {
	vector<pair<int, int>> result;
	int n = (int)h.size();
	if (n < 2) return result;
	for (int i = 0, j = 1; i < j; i++) {
		while (true) {
			result.push_back({i, j});
			if (cross(h[(i + 1) % n] - h[i], 
								h[(j + 1) % n] - h[j]) <= 0) break;
			j = (j + 1) % n;
	}}
	return result;
}
