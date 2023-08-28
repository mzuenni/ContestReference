vector<vector<int>> adj;
// pairs ist der gematchte Knoten oder -1
vector<int> pairs, dist, ptr;

bool bfs(int l) {
	queue<int> q;
	for(int v = 0; v < l; v++) {
		if (pairs[v] < 0) {dist[v] = 0; q.push(v);}
		else dist[v] = -1;
	}
	bool exist = false;
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for (int u : adj[v]) {
			if (pairs[u] < 0) {exist = true; continue;}
			if (dist[pairs[u]] < 0) {
				dist[pairs[u]] = dist[v] + 1;
				q.push(pairs[u]);
	}}}
	return exist;
}

bool dfs(int v) {
	for (; ptr[v] < sz(adj[v]); ptr[v]++) {
		int u = adj[v][ptr[v]];
		if (pairs[u] < 0 ||
		   (dist[pairs[u]] > dist[v] && dfs(pairs[u]))) {
			pairs[u] = v; pairs[v] = u;
			return true;
	}}
	return false;
}

int hopcroft_karp(int l) { // l = #Knoten links
	int ans = 0;
	pairs.assign(sz(adj), -1);
	dist.resize(l);
	// Greedy Matching, optionale Beschleunigung.
	for (int v = 0; v < l; v++) for (int u : adj[v])
		if (pairs[u] < 0) {pairs[u] = v; pairs[v] = u; ans++; break;}
	while(bfs(l)) {
		ptr.assign(l, 0);
		for(int v = 0; v < l; v++) {
			if (pairs[v] < 0) ans += dfs(v);
	}}
	return ans;
}
