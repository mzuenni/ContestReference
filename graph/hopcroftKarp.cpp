vector<vector<int>> adj;
// pairs ist der gematchte Knoten oder -1
vector<int> pairs, dist, ptr;

bool bfs(int l) {
	queue<int> q;
	for(int i = 0; i < l; i++) {
		if (pairs[i] < 0) {dist[i] = 0; q.push(i);}
		else dist[i] = -1;
	}
	bool exist = false;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : adj[u]) {
			if (pairs[v] < 0) {exist = true; continue;}
			if (dist[pairs[v]] < 0) {
				dist[pairs[v]] = dist[u] + 1;
				q.push(pairs[v]);
	}}}
	return exist;
}

bool dfs(int u) {
	for (; ptr[u] < sz(adj[u]); ptr[u]++) {
		int v = adj[u][ptr[u]];
		if (pairs[v] < 0 ||
		   (dist[pairs[v]] > dist[u] && dfs(pairs[v]))) {
			pairs[v] = u; pairs[u] = v;
			return true;
	}}
	return false;
}

int hopcroft_karp(int l) { // l = #Knoten links
	int ans = 0;
	pairs.assign(sz(adj), -1);
	dist.resize(l);
	// Greedy Matching, optionale Beschleunigung.
	for (int i = 0; i < l; i++) for (int w : adj[i])
		if (pairs[w] < 0) {pairs[i] = w; pairs[w] = i; ans++; break;}
	while(bfs(l)) {
		ptr.assign(l, 0);
		for(int i = 0; i < l; i++) {
			if (pairs[i] < 0) ans += dfs(i);
	}}
	return ans;
}
