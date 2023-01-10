struct connect {
	int n;
	vector<pair<int, int>> edges;
	LCT lct; // min LCT no updates required
	
	connect(int n, int m) : n(n), edges(m), lct(n+m) {}
	
	bool connected(int a, int b) {
		return lct.connected(&lct.nodes[a], &lct.nodes[b]);
	}
	
	void addEdge(int a, int b, int id) {
		lct.nodes[id + n] = LCT::Node(id + n, id + n);
		edges[id] = {a, b};
		if (connected(a, b)) {
			int old = lct.query(&lct.nodes[a], &lct.nodes[b]);
			if (old < id) eraseEdge(old);
		}
		if (!connected(a, b)) {
			lct.link(&lct.nodes[a], &lct.nodes[id + n]);
			lct.link(&lct.nodes[b], &lct.nodes[id + n]);
	}}
	
	void eraseEdge(ll id) {
		if (connected(edges[id].first, edges[id].second) &&
			lct.query(&lct.nodes[edges[id].first], 
			          &lct.nodes[edges[id].second]) == id) {
			lct.cut(&lct.nodes[edges[id].first], &lct.nodes[id + n]);
			lct.cut(&lct.nodes[edges[id].second], &lct.nodes[id + n]);
	}}
};