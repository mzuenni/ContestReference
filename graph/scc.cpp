vector<vector<int>> adjlist;

int counter, sccCounter;
vector<bool> inStack;
vector<vector<int>> sccs;
// idx enthält den Index der SCC pro Knoten.
vector<int> d, low, idx, s;

void visit(int v) {
	d[v] = low[v] = counter++;
	s.push_back(v); inStack[v] = true;

	for (auto u : adjlist[v]) {
		if (d[u] < 0) {
			visit(u);
			low[v] = min(low[v], low[u]);
		} else if (inStack[u]) {
			low[v] = min(low[v], low[u]);
	}}

	if (d[v] == low[v]) {
		sccs.push_back({});
		int u;
		do {
			u = s.back(); s.pop_back(); inStack[u] = false;
			idx[u] = sccCounter;
			sccs[sccCounter].push_back(u);
		} while (u != v);
		sccCounter++;
}}

void scc() {
	inStack.assign(sz(adjlist), false);
	d.assign(sz(adjlist), -1);
	low.assign(sz(adjlist), -1);
	idx.assign(sz(adjlist), -1);

	counter = sccCounter = 0;
	for (int i = 0; i < sz(adjlist); i++) {
		if (d[i] < 0) visit(i);
}}
