vector<vector<edge>> adj;
vector<int> num;
int counter, rootCount, root;
vector<bool> isArt;
vector<edge> bridges, st;
vector<vector<edge>> bcc;

int dfs(int v, int parent = -1) {
	int me = num[v] = ++counter, top = me;
	for (edge& e : adj[v]) {
		if (e.id == parent){}
		else if (num[e.to]) {
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
				bcc.emplace_back();
				while (sz(st) > si) {
					bcc.back().push_back(st.back());
					st.pop_back();
	}}}}
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
