vector<vector<Edge>> adj;
vector<int> num;
int counter, rootCount, root;
vector<bool> isArt;
vector<Edge> bridges, st;
vector<vector<Edge>> bcc;

int dfs(int v, int from = -1) {
	int me = num[v] = ++counter, top = me;
	for (Edge& e : adj[v]) {
		if (e.id == from) continue;
		if (num[e.to]) {
			top = min(top, num[e.to]);
			if (num[e.to] < me) st.push_back(e);
		} else {
			if (v == root) rootCount++;
			int si = sz(st);
			int up = dfs(e.to, e.id);
			top = min(top, up);
			if (up >= me) isArt[v] = true;
			if (up > me) bridges.push_back(e);
			if (up <= me) st.push_back(e);
			if (up == me) {
				bcc.emplace_back(si + all(st));
				st.resize(si);
	}}}
	return top;
}

void find() {
	counter = 0;
	num.assign(sz(adj), 0);
	isArt.assign(sz(adj), false);
	bridges.clear();
	st.clear();
	bcc.clear();
	for (int v = 0; v < sz(adj); v++) {
		if (!num[v]) {
			root = v;
			rootCount = 0;
			dfs(v);
			isArt[v] = rootCount > 1;
}}}
