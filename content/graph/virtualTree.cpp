// needs dfs in- and out- time and lca function
vector<int> in, out;

void virtualTree(vector<int> ind) { // indices of used nodes
	sort(all(ind), [&](int x, int y) {return in[x] < in[y];});
	for (int i=0; i<sz(a)-1; i++) {
		ind.push_back(lca(ind[i], ind[i+1]));
	}
	sort(all(ind), [&](int x, int y) {return in[x] < in[y];});
	ind.erase(unique(all(ind)), ind.end());

	int n = ind.size();
	vector<vector<int>> tree(n);
	vector<int> st = {0};
	for (int i=1; i<n; i++) {
		while (in[ind[i]] >= out[ind[st.back()]]) st.pop_back();
		tree[st.back()].push_back(i);
		st.push(i);
	}
	// virtual directed tree with n nodes, original indices in ind
	// weights can be calculated, e.g. with binary lifting
}
