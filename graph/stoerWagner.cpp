struct edge {
	int from, to;
	ll cap;
};

vector<vector<edge>> adj, tmp;
vector<bool> erased;

void merge(int a, int b) {
	tmp[a].insert(tmp[a].end(), all(tmp[b]));
	tmp[b].clear();
	erased[b] = true;
	for (auto& v : tmp) {
		for (auto&e : v) {
			if (e.from == b) e.from = a;
			if (e.to == b) e.to = a;
}}}

ll stoer_wagner() {
	ll res = INF;
	tmp = adj;
	erased.assign(sz(tmp), false);
	for (int i = 1; i < sz(tmp); i++) {
		int s = 0;
		while (erased[s]) s++;
		priority_queue<pair<ll, int>> pq;
		pq.push({0, s});
		vector<ll> con(sz(tmp));
		ll cur = 0;
		vector<pair<ll, int>> state;
		while (!pq.empty()) {
			int c = pq.top().second;
			pq.pop();
			if (con[c] < 0) continue; //already seen
			con[c] = -1;
			for (auto e : tmp[c]) {
				if (con[e.to] >= 0) {//add edge to cut
					con[e.to] += e.cap;
					pq.push({con[e.to], e.to});
					cur += e.cap;
				} else if (e.to != c) {//remove edge from cut
					cur -= e.cap;
			}}
			state.push_back({cur, c});
		}
		int t = state.back().second;
		state.pop_back();
		if (state.empty()) return 0; //graph is not connected?!
		merge(state.back().second, t);
		res = min(res, state.back().first);
	}
	return res;
}
