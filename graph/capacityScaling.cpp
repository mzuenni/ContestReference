struct edge {
	int from, to;
	ll f, c;
};

vector<edge> edges;
vector<vector<int>> adj;
int s, t, dfsCounter;
vector<int> visited;
ll capacity;

void addEdge(int from, int to, ll c) {
	adj[from].push_back(sz(edges));
	edges.push_back({from, to, 0, c});
	adj[to].push_back(sz(edges));
	edges.push_back({to, from, 0, 0});
}

bool dfs(int x) {
	if (x == t) return true;
	if (visited[x] == dfsCounter) return false;
	visited[x] = dfsCounter;
	for (int id : adj[x]) {
		if (edges[id].c >= capacity && dfs(edges[id].to)) {
			edges[id].c -= capacity; edges[id ^ 1].c += capacity;
			edges[id].f += capacity; edges[id ^ 1].f -= capacity;
			return true;
	}}
	return false;
}

ll maxFlow(int source, int target) {
	capacity = 1ll << 62;
	s = source;
	t = target;
	ll flow = 0;
	visited.assign(sz(adj), 0);
	dfsCounter = 0;
	while (capacity) {
		while (dfsCounter++, dfs(s)) flow += capacity;
		capacity /= 2;
	}
	return flow;
}
