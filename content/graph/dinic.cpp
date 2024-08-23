struct Edge {
	int to, rev;
	ll f, c;
};

vector<vector<Edge>> adj;
int s, t;
vector<int> pt, dist;

void addEdge(int u, int v, ll c) {
	adj[u].push_back({v, (int)sz(adj[v]), 0, c});
	adj[v].push_back({u, (int)sz(adj[u]) - 1, 0, 0});
}

bool bfs() {
	dist.assign(sz(adj), -1);
	dist[s] = 0;
	queue<int> q({s});
	while (!q.empty() && dist[t] < 0) {
		int v = q.front(); q.pop();
		for (Edge& e : adj[v]) {
			if (dist[e.to] < 0 && e.c - e.f > 0) {
				dist[e.to] = dist[v] + 1;
				q.push(e.to);
	}}}
	return dist[t] >= 0;
}

ll dfs(int v, ll flow = INF) {
	if (v == t || flow == 0) return flow;
	for (; pt[v] < sz(adj[v]); pt[v]++) {
		Edge& e = adj[v][pt[v]];
		if (dist[e.to] != dist[v] + 1) continue;
		ll cur = dfs(e.to, min(e.c - e.f, flow));
		if (cur > 0) {
			e.f += cur;
			adj[e.to][e.rev].f -= cur;
			return cur;
	}}
	return 0;
}

ll maxFlow(int source, int target) {
	s = source, t = target;
	ll flow = 0;
	while (bfs()) {
		pt.assign(sz(adj), 0);
		ll cur;
		do {
			cur = dfs(s);
			flow += cur;
		} while (cur > 0);
	}
	return flow;
}
