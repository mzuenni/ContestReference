struct Edge {
	int from, to;
	ll cap;
};

vector<vector<Edge>> adj, tmp;
vector<bool> erased;

void merge(int u, int v) {
	tmp[u].insert(tmp[u].end(), all(tmp[v]));
	tmp[v].clear();
	erased[v] = true;
	for (auto& vec : tmp) {
		for (Edge& e : vec) {
			if (e.from == v) e.from = u;
			if (e.to == v) e.to = u;
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
