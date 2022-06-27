vector<vector<int>> adj;
vector<int> sz, in, out, nxt, par;
int t;

void dfs_sz(int v = 0, int from = -1) {
	sz[v] = 1;
	for (auto& u : adj[v]) {
		if (u != from) {
			dfs_sz(u, v);
			sz[v] += sz[u];
		}
		if (adj[v][0] == from || sz[u] > sz[adj[v][0]]) {
			swap(u, adj[v][0]);
}}}

void dfs_hld(int v = 0, int from = -1) {
	par[v] = from;
	in[v] = t++;
	for (int u : adj[v]) {
		if (u == from) continue;
		nxt[u] = (u == adj[v][0] ? nxt[v] : u);
		dfs_hld(u, v);
	}
	out[v] = t;
}

void init() {
	int n = sz(adj);
	sz.assign(n, 0); in.assign(n, 0); out.assign(n, 0);
	nxt.assign(n, 0); par.assign(n, -1);
	t = 0;
	dfs_sz(); dfs_hld();
}

vector<pair<int, int>> get_intervals(int u, int v) {
	vector<pair<int, int>> res;
	while (true) {
		if (in[v] < in[u]) swap(u, v);
		if (in[nxt[v]] <= in[u]) {
			res.eb(in[u], in[v] + 1);
			return res;
		}
		res.eb(in[nxt[v]], in[v] + 1);
		v = par[nxt[v]];
}}

int get_lca(int u, int v) {
	while (true) {
		if (in[v] < in[u]) swap(u, v);
		if (in[nxt[v]] <= in[u]) return in[u];
		v = par[nxt[v]];
}}
