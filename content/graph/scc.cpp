vector<vector<int>> adj, sccs;
int counter;
vector<bool> inStack;
vector<int> low, idx, s; //idx enthält Index der SCC pro Knoten.

void visit(int v) {
	int old = low[v] = counter++;
	s.push_back(v); inStack[v] = true;

	for (auto u : adj[v]) {
		if (low[u] < 0) visit(u);
		if (inStack[u]) low[v] = min(low[v], low[u]);
	}

	if (old == low[v]) {
		sccs.push_back({});
		for (int u = -1; u != v;) {
			u = s.back(); s.pop_back(); inStack[u] = false;
			idx[u] = sz(sccs) - 1;
			sccs.back().push_back(u);
}}}

void scc() {
	inStack.assign(sz(adj), false);
	low.assign(sz(adj), -1);
	idx.assign(sz(adj), -1);
	sccs.clear();

	counter = 0;
	for (int i = 0; i < sz(adj); i++) {
		if (low[i] < 0) visit(i);
}}
