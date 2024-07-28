struct Edge {
	int to, rev;
	ll f, c;
};

vector<vector<Edge>> adj;
vector<vector<int>> hs;
vector<ll> ec;
vector<int> cur, H;

void addEdge(int u, int v, ll c) {
	adj[u].push_back({v, (int)sz(adj[v]), 0, c});
	adj[v].push_back({u, (int)sz(adj[u])-1, 0, 0});
}

void addFlow(Edge& e, ll f) {
	if (ec[e.to] == 0 && f > 0)
		hs[H[e.to]].push_back(e.to);
	e.f += f;
	adj[e.to][e.rev].f -= f;
	ec[e.to] += f;
	ec[adj[e.to][e.rev].to] -= f;
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
	for (Edge& e : adj[s]) addFlow(e, e.c);
	for (int hi = 0;;) {
		while (hs[hi].empty()) if (!hi--) return -ec[s];
		int v = hs[hi].back();
		hs[hi].pop_back();
		while (ec[v] > 0) {
			if (cur[v] == sz(adj[v])) {
				H[v] = 2*n;
				for (int i = 0; i < sz(adj[v]); i++) {
					Edge& e = adj[v][i];
					if (e.c - e.f > 0 &&
					    H[v] > H[e.to] + 1) {
						H[v] = H[e.to] + 1;
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
				Edge& e = adj[v][cur[v]];
				if (e.c - e.f > 0 && H[v] == H[e.to] + 1) {
					addFlow(adj[v][cur[v]], min(ec[v], e.c - e.f));
				} else {
					cur[v]++;
}}}}}
