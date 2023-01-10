struct edge {
	int from, to; 
	ll f, c;
};

vector<edge> edges;
vector<vector<int>> adjlist, hs;
vector<ll> ec;
vector<int> cur, H;

void addEdge(int from, int to, ll c) {
	adjlist[from].push_back(sz(edges));
	edges.push_back({from, to, 0, c});
	adjlist[to].push_back(sz(edges));
	edges.push_back({to, from, 0, 0});
}

void addFlow(int id, ll f) {
	if (ec[edges[id].to] == 0 && f > 0)
		hs[H[edges[id].to]].push_back(edges[id].to);
	edges[id].f += f;
	edges[id^1].f -= f;
	ec[edges[id].to] += f;
	ec[edges[id].from] -= f;
}

ll maxFlow(int s, int t) {
	int n = sz(adjlist);
	hs.assign(2*n, {});
	ec.assign(n, 0);
	cur.assign(n, 0);
	H.assign(n, 0);
	H[s] = n;
	ec[t] = 1;//never set t to active...
	vector<int> co(2*n);
	co[0] = n - 1;
	for (int id : adjlist[s]) addFlow(id, edges[id].c);
	for (int hi = 0;;) {
		while (hs[hi].empty()) if (!hi--) return -ec[s];
		int u = hs[hi].back();
		hs[hi].pop_back();
		while (ec[u] > 0) {
			if (cur[u] == sz(adjlist[u])) {
				H[u] = 2*n;
				for (int i = 0; i < sz(adjlist[u]); i++) {
					int id = adjlist[u][i];
					if (edges[id].c - edges[id].f > 0 &&
					    H[u] > H[edges[id].to] + 1) {
						H[u] = H[edges[id].to] + 1;
						cur[u] = i;
				}}
				co[H[u]]++;
				if (!--co[hi] && hi < n) {
					for (int i = 0; i < n; i++) {
						if (hi < H[i] && H[i] < n) {
							co[H[i]]--;
							H[i] = n + 1;
				}}}
				hi = H[u];
			} else {
				auto e = edges[adjlist[u][cur[u]]];
				if (e.c - e.f > 0 && H[u] == H[e.to] + 1) {
					addFlow(adjlist[u][cur[u]], min(ec[u], e.c - e.f));
				} else {
					cur[u]++;
}}}}}
