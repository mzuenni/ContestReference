using bits = bitset<64>;
vector<bits> adj, cliques;

void addEdge(int a, int b) {
	if (a != b) adj[a][b] = adj[b][a] = 1;
}

void bronKerboschRec(bits R, bits P, bits X) {
	if (P.none() && X.none()) {
		cliques.push_back(R);
	} else {
		int q = min(P._Find_first(), X._Find_first());
		bits cands = P & ~adj[q];
		for (int i = 0; i < sz(adj); i++) if (cands[i]) {
			R[i] = 1;
			bronKerboschRec(R, P & adj[i], X & adj[i]);
			R[i] = P[i] = 0;
			X[i] = 1;
}}}

void bronKerbosch() {
	cliques.clear();
	bronKerboschRec({}, {(1ull << sz(adj)) - 1}, {});
}
