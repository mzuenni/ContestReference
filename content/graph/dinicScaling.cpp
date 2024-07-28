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

bool bfs(ll lim) {
	dist.assign(sz(adj), -1);
	dist[s] = 0;
	queue<int> q({s});
	while (!q.empty() && dist[t] < 0) {
		int v = q.front(); q.pop();
		for (Edge& e : adj[v]) {
			if (dist[e.to] < 0 && e.c - e.f >= lim) {
				dist[e.to] = dist[v] + 1;
				q.push(e.to);
	}}}
	return dist[t] >= 0;
}

bool dfs(int v, ll flow) {
	if (v == t) return true;
	for (; pt[v] < sz(adj[v]); pt[v]++) {
		Edge& e = adj[v][pt[v]];
		if (dist[e.to] != dist[v] + 1) continue;
		if (e.c - e.f >= flow && dfs(e.to, flow)) {
			e.f += flow;
			adj[e.to][e.rev].f -= flow;
			return true;
	}}
	return false;
}

ll maxFlow(int source, int target) {
	s = source, t = target;
	ll flow = 0;
	for (ll lim = (1LL << 62); lim >= 1; lim /= 2) {
		while (bfs(lim)) {
			pt.assign(sz(adj), 0);
			while (dfs(s, lim)) flow += lim;
	}}
	return flow;
}
