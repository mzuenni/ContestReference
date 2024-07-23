struct connect {
	int n;
	vector<pair<int, int>> edges;
	LCT lct; // min LCT @\sourceref{datastructures/LCT.cpp}@, no updates required

	connect(int n, int m) : n(n), edges(m), lct(n+m) {}

	bool connected(int u, int v) {
		return lct.connected(&lct.nodes[u], &lct.nodes[v]);
	}

	void addEdge(int u, int v, int id) {
		lct.nodes[id + n] = LCT::Node(id + n, id + n);
		edges[id] = {u, v};
		if (connected(u, v)) {
			int old = lct.query(&lct.nodes[u], &lct.nodes[v]);
			if (old < id) eraseEdge(old);
		}
		if (!connected(u, v)) {
			lct.link(&lct.nodes[u], &lct.nodes[id + n]);
			lct.link(&lct.nodes[v], &lct.nodes[id + n]);
	}}

	void eraseEdge(ll id) {
		if (connected(edges[id].first, edges[id].second) &&
			lct.query(&lct.nodes[edges[id].first],
			          &lct.nodes[edges[id].second]) == id) {
			lct.cut(&lct.nodes[edges[id].first], &lct.nodes[id + n]);
			lct.cut(&lct.nodes[edges[id].second], &lct.nodes[id + n]);
	}}
};
