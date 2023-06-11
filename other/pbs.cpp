// Q = # of queries, bucket sort is sometimes faster
vector<int> low(Q, 0), high(Q, MAX_OPERATIONS);
while (true) {
	vector<pair<int, int>> focus;
	for (int i = 0; i < Q; i++) if (low[i] < high[i]) {
		focus.emplace_back((low[i] + high[i]) / 2, i);
	}
	if (focus.empty()) break;
	sort(all(focus));

	// reset simulation
	for (int step = 0; auto [mid, i] : focus) {
		while (step <= mid) {
			// simulation step
			step++;
		}
		if (/* requirement already fulfilled */) high[i] = mid;
		else low[i] = mid + 1;
}} // answer in low (and high)
