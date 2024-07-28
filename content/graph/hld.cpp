vector<vector<int>> adj;
vector<int> sz, in, out, nxt, par;
int counter;

void dfs_sz(int v = 0, int from = -1) {
	for (auto& u : adj[v]) if (u != from) {
		dfs_sz(u, v);
		sz[v] += sz[u];
		if (adj[v][0] == from || sz[u] > sz[adj[v][0]]) {
			swap(u, adj[v][0]); //changes adj!
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
	sz.assign(n, 1), nxt.assign(n, root), par.assign(n, -1);
	in.resize(n), out.resize(n);
	counter = 0;
	dfs_sz(root);
	dfs_hld(root);
}

template<typename F>
void for_intervals(int u, int v, F&& f) {
	for (;; v = par[nxt[v]]) {
		if (in[v] < in[u]) swap(u, v);
		f(max(in[u], in[nxt[v]]), in[v] + 1);
		if (in[nxt[v]] <= in[u]) return;
}}

int get_lca(int u, int v) {
	for (;; v = par[nxt[v]]) {
		if (in[v] < in[u]) swap(u, v);
		if (in[nxt[v]] <= in[u]) return u;
}}
