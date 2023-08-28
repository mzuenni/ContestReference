vector<vector<int>> idx;
vector<int> to, validIdx, cycle;
vector<bool> used;

void addEdge(int u, int v) {
	idx[u].push_back(sz(to));
	to.push_back(v);
	used.push_back(false);
	idx[v].push_back(sz(to)); // für ungerichtet
	to.push_back(u);
	used.push_back(false);
}

void euler(int v) { // init idx und validIdx
	for (;validIdx[v] < sz(idx[v]); validIdx[v]++) {
		if (!used[idx[v][validIdx[v]]]) {
			int u = to[idx[v][validIdx[v]]];
			used[idx[v][validIdx[v]]] = true;
			used[idx[v][validIdx[v]] ^ 1] = true; // für ungerichtet
			euler(u);
	}}
	cycle.push_back(v); // Zyklus in umgekehrter Reihenfolge.
}
