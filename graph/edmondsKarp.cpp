int s, t, f; //source, target, single flow
int res[MAX_V][MAX_V]; //adj-matrix
vector< vector<int> > adjlist;
int p[MAX_V]; //bfs spanning tree

void augment(int v, int minEdge) {
	if (v == s) { f = minEdge; return; }
	else if (p[v] != -1) {
		augment(p[v], min(minEdge, res[p[v]][v]));
		res[p[v]][v] -= f; res[v][p[v]] += f;
}}

int maxFlow() { //first inititalize res, adjList, s and t
	int mf = 0;
	while (true) {
		f = 0;
		bitset<MAX_V> vis; vis[s] = true;
		queue<int> q; q.push(s);
		memset(p, -1, sizeof(p));
		while (!q.empty()) { //BFS
			int u = q.front(); q.pop();
			if (u == t) break;
			for (int j = 0; j < (int)adjlist[u].size(); j++) {
				int v = adjlist[u][j];
				if (res[u][v] > 0 && !vis[v]) {
					vis[v] = true; q.push(v); p[v] = u;
		}}}
		
		augment(t, INF); //add found path to max flow
		if (f == 0) break;
		mf += f;
	}
	return mf;
}
