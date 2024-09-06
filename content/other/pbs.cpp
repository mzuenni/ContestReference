// Q = # of queries, bucket sort is sometimes faster
vector<int> low(Q, -1), high(Q, MAX_OPERATIONS);
while (true) {
	vector<pair<int, int>> focus;
	for (int i = 0; i < Q; i++) {
		if (low[i] + 1 < high[i]) {
			focus.emplace_back((low[i] + high[i]) / 2, i);
	}}
	if (focus.empty()) break;
	sort(all(focus));

	// reset simulation
	for (int step = 0; auto [mid, i] : focus) {
		for (; step <= mid; step++) {
			// simulation step
		}
		if (/* requirement already fulfilled */) high[i] = mid;
		else low[i] = mid;
}} // answer in low (MAX_OPERATIONS if never ok)
