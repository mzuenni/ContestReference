constexpr ll INF = 1LL << 60; // Größer als der maximale Fluss.
struct MinCostFlow {
	struct edge {
		int to;
		ll f, cost;
	};
	vector<edge> edges;
	vector<vector<int>> adj;
	vector<int> pref, con;
	vector<ll> dist;
	const int s, t;
	ll maxflow, mincost;

	MinCostFlow(int n, int source, int target) :
		adj(n), s(source), t(target) {};

	void addEdge(int u, int v, ll c, ll cost) {
		adj[u].push_back(sz(edges));
		edges.push_back({v, c, cost});
		adj[v].push_back(sz(edges));
		edges.push_back({u, 0, -cost});
	}

	bool SPFA() {
		pref.assign(sz(adj), -1);
		dist.assign(sz(adj), INF);
		vector<bool> inqueue(sz(adj));
		queue<int> queue;
		dist[s] = 0;
		queue.push(s);
		pref[s] = s;
		inqueue[s] = true;
		while (!queue.empty()) {
			int cur = queue.front(); queue.pop();
			inqueue[cur] = false;
			for (int id : adj[cur]) {
				int to = edges[id].to;
				if (edges[id].f > 0 &&
				    dist[to] > dist[cur] + edges[id].cost) {
					dist[to] = dist[cur] + edges[id].cost;
					pref[to] = cur;
					con[to] = id;
					if (!inqueue[to]) {
						inqueue[to] = true;
						queue.push(to);
		}}}}
		return pref[t] != -1;
	}

	void extend() {
		ll w = INF;
		for (int u = t; pref[u] != u; u = pref[u])
			w = min(w, edges[con[u]].f);
		maxflow += w;
		mincost += dist[t] * w;
		for (int u = t; pref[u] != u; u = pref[u]) {
			edges[con[u]].f -= w;
			edges[con[u] ^ 1].f += w;
	}}

	void mincostflow() {
		con.assign(sz(adj), 0);
		maxflow = mincost = 0;
		while (SPFA()) extend();
	}
};
