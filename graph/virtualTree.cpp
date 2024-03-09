// needs dfs in- and out- time and lca function
vector<int> in, out;

void virtualTree(const vector<int>& a) { // takes indices of used nodes
	auto ind = a;
	sort(all(ind), [&](int x, int y) {return in[x] < in[y];});

	for (int i=0; i<sz(a)-1; i++) {
		ind.push_back(lca(ind[i], ind[i+1]));
	}
	sort(all(ind), [&](int x, int y) {return in[x] < in[y];});
	ind.erase(unique(all(ind)), ind.end());

	int n = ind.size();
	vector<vector<int>> tree(n);
	stack<int> st{{0}};
	for (int i=1; i<n; i++) {
		while (in[ind[i]] >= out[ind[st.top()]]) st.pop();
		tree[st.top()].push_back(i);
		st.push(i);
	}

	// virtual directed tree with n nodes, original indices in ind
	// weights can be calculated if necessary, e.g. with binary lifting
}
