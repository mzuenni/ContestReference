struct Edge {
	int from, to;
	ll f, c;
};

vector<Edge> edges;
vector<vector<int>> adj, hs;
vector<ll> ec;
vector<int> cur, H;

void addEdge(int from, int to, ll c) {
	adj[from].push_back(sz(edges));
	edges.push_back({from, to, 0, c});
	adj[to].push_back(sz(edges));
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
	int n = sz(adj);
	hs.assign(2*n, {});
	ec.assign(n, 0);
	cur.assign(n, 0);
	H.assign(n, 0);
	H[s] = n;
	ec[t] = 1;//never set t to active...
	vector<int> co(2*n);
	co[0] = n - 1;
	for (int id : adj[s]) addFlow(id, edges[id].c);
	for (int hi = 0;;) {
		while (hs[hi].empty()) if (!hi--) return -ec[s];
		int v = hs[hi].back();
		hs[hi].pop_back();
		while (ec[v] > 0) {
			if (cur[v] == sz(adj[v])) {
				H[v] = 2*n;
				for (int i = 0; i < sz(adj[v]); i++) {
					int id = adj[v][i];
					if (edges[id].c - edges[id].f > 0 &&
					    H[v] > H[edges[id].to] + 1) {
						H[v] = H[edges[id].to] + 1;
						cur[v] = i;
				}}
				co[H[v]]++;
				if (!--co[hi] && hi < n) {
					for (int i = 0; i < n; i++) {
						if (hi < H[i] && H[i] < n) {
							co[H[i]]--;
							H[i] = n + 1;
				}}}
				hi = H[v];
			} else {
				auto e = edges[adj[v][cur[v]]];
				if (e.c - e.f > 0 && H[v] == H[e.to] + 1) {
					addFlow(adj[v][cur[v]], min(ec[v], e.c - e.f));
				} else {
					cur[v]++;
}}}}}
