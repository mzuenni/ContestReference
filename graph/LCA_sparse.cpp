struct LCA {
	vector<ll> depth;
	vector<int> visited, first;
	int idx;
	SparseTable st; //sparse table von oben

	void init(vector<vector<int>>& g, int root) {
		depth.assign(2 * sz(g), 0);
		visited.assign(2 * sz(g), -1);
		first.assign(sz(g), 2 * sz(g));
		idx = 0;
		visit(g, root);
		st.init(&depth);
	}

	void visit(vector<vector<int>>& g, int v, ll d=0, int p=-1) {
		visited[idx] = v, depth[idx] = d;
		first[v] = min(idx, first[v]), idx++;

		for (int w : g[v]) {
			if (first[w] == 2 * sz(g)) {
				visit(g, w, d + 1, v);
				visited[idx] = v, depth[idx] = d, idx++;
	}}}

	int getLCA(int a, int b) {
		if (first[a] > first[b]) swap(a, b);
		return visited[st.queryIdempotent(first[a], first[b] + 1)];
	}

	ll getDepth(int a) {return depth[first[a]];}
};
