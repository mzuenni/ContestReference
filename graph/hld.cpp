vector<vector<int>> adj;
vector<int> sz, in, out, nxt, par;
int counter;

void dfs_sz(int v = 0, int from = -1) {
	for (auto& u : adj[v]) if (u != from) {
		dfs_sz(u, v);
		sz[v] += sz[u];
		if (adj[v][0] == from || sz[u] > sz[adj[v][0]]) {
			swap(u, adj[v][0]);
}}}

void dfs_hld(int v = 0, int from = -1) {
	par[v] = from;
	in[v] = counter++;
	for (int u : adj[v]) if (u != from) {
		nxt[u] = (u == adj[v][0]) ? nxt[v] : u;
		dfs_hld(u, v);
	}
	out[v] = counter;
}

void init(int root = 0) {
	int n = sz(adj);
	sz.assign(n, 1), nxt.assign(n, 0), par.assign(n, -1);
	in.resize(n), out.resize(n);
	counter = 0;
	dfs_sz(root); dfs_hld(root);
}

vector<pair<int, int>> get_intervals(int u, int v) {
	vector<pair<int, int>> res;
	while (true) {
		if (in[v] < in[u]) swap(u, v);
		if (in[nxt[v]] <= in[u]) {
			res.emplace_back(in[u], in[v] + 1);
			return res;
		}
		res.emplace_back(in[nxt[v]], in[v] + 1);
		v = par[nxt[v]];
}}

int get_lca(int u, int v) {
	while (true) {
		if (in[v] < in[u]) swap(u, v);
		if (in[nxt[v]] <= in[u]) return u;
		v = par[nxt[v]];
}}
