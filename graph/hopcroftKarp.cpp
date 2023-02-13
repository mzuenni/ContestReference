vector<vector<int>> adjlist;
// pairs ist der gematchte Knoten oder -1
vector<int> pairs, dist;

bool bfs(int n) {
	queue<int> q;
	for(int i = 0; i < n; i++) {
		if (pairs[i] < 0) {dist[i] = 0; q.push(i);}
		else dist[i] = -1;
	}
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : adjlist[u]) {
			if (pairs[v] < 0) return true;
			if (dist[pairs[v]] < 0) {
				dist[pairs[v]] = dist[u] + 1;
				q.push(pairs[v]);
	}}}
	return false;
}

bool dfs(int u) {
	for (int v : adjlist[u]) {
		if (pairs[v] < 0 ||
		   (dist[pairs[v]] > dist[u] && dfs(pairs[v]))) { 
			pairs[v] = u; pairs[u] = v; 
			return true;
	}}
	dist[u] = -1;
	return false;
}

int hopcroft_karp(int n) { // n = #Knoten links
	int ans = 0;
	pairs.assign(sz(adjlist), -1);
	dist.resize(n);
	// Greedy Matching, optionale Beschleunigung.
	for (int i = 0; i < n; i++) for (int w : adjlist[i])
		if (pairs[w] < 0) {pairs[i] = w; pairs[w] = i; ans++; break;}
	while(bfs(n)) for(int i = 0; i < n; i++)
		if (pairs[i] < 0) ans += dfs(i);
	return ans;
}
