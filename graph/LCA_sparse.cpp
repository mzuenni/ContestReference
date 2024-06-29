struct LCA {
	vector<ll> depth;
	vector<int> visited, first;
	int idx;
	SparseTable st; //sparse table @\sourceref{datastructures/sparseTable.cpp}@

	void init(vector<vector<int>>& adj, int root) {
		depth.assign(2 * sz(adj), 0);
		visited.assign(2 * sz(adj), -1);
		first.assign(sz(adj), 2 * sz(adj));
		idx = 0;
		dfs(adj, root);
		st.init(&depth);
	}

	void dfs(vector<vector<int>>& adj, int v, ll d=0, int p=-1) {
		visited[idx] = v, depth[idx] = d;
		first[v] = min(idx, first[v]), idx++;

		for (int u : adj[v]) {
			if (first[u] == 2 * sz(adj)) {
				dfs(adj, u, d + 1, v);
				visited[idx] = v, depth[idx] = d, idx++;
	}}}

	int getLCA(int u, int v) {
		if (first[u] > first[v]) swap(u, v);
		return visited[st.queryIdempotent(first[u], first[v] + 1)];
	}

	ll getDepth(int v) {return depth[first[v]];}
};
