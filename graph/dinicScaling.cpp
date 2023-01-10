struct edge {
	int from, to; 
	ll f, c;
};

vector<edge> edges;
vector<vector<int>> adjlist;
int s, t;
vector<int> pt, dist;
ll flow, lim;
queue<int> q;

void addEdge(int from, int to, ll c) {
	adjlist[from].push_back(sz(edges));
	edges.push_back({from, to, 0, c});
	adjlist[to].push_back(sz(edges));
	edges.push_back({to, from, 0, 0});
}

bool bfs() {
	dist.assign(sz(dist), -1);
	dist[t] = sz(adjlist) + 1; 
	q.push(t);
	while (!q.empty() && dist[s] < 0) {
		int cur = q.front(); q.pop();
		for (int id : adjlist[cur]) {
			int to = edges[id].to;
			if (dist[to] < 0 &&
			    edges[id ^ 1].c - edges[id ^ 1].f >= lim) {
				dist[to] = dist[cur] - 1;
				q.push(to);
	}}}
	while (!q.empty()) q.pop();
	return dist[s] >= 0;
}

bool dfs(int v, ll flow) {
	if (flow == 0) return false;
	if (v == t) return true;
	for (; pt[v] < sz(adjlist[v]); pt[v]++) {
		int id = adjlist[v][pt[v]], to = edges[id].to;
		if (dist[to] == dist[v] + 1 && 
		    edges[id].c - edges[id].f >= flow) {
			if (dfs(to, flow)) {
				edges[id].f += flow;
				edges[id ^ 1].f -= flow;
				return true;
	}}}
	return false;
}

ll maxFlow(int source, int target) {
	s = source;
	t = target;
	flow = 0;
	dist.resize(sz(adjlist));
	for (lim = (1LL << 62); lim >= 1;) {
		if (!bfs()) {lim /= 2; continue;}
		pt.assign(sz(adjlist), 0);
		while (dfs(s, lim)) flow += lim;
	}
	return flow;
}
