constexpr int maxEdges = 128;
using cycle = bitset<maxEdges>;
struct cylces {
	vector<vector<pair<int, int>>> adj;
	vector<bool> seen;
	vector<cycle> paths, base;
	vector<pair<int, int>> edges;

	cylces(int n) : adj(n), seen(n), paths(n) {}

	void addEdge(int u, int v) {
		adj[u].push_back({v, sz(edges)});
		adj[v].push_back({u, sz(edges)});
		edges.push_back({u, v});
	}

	void addBase(cycle cur) {
		for (cycle o : base) {
			o ^= cur;
			if (o._Find_first() > cur._Find_first()) cur = o;
		}
		if (cur.any()) base.push_back(cur);
	}

	void findBase(int v = 0, int from = -1, cycle cur = {}) {
		if (adj.empty()) return;
		if (seen[v]) {
			addBase(cur ^ paths[v]);
		} else {
			seen[v] = true;
			paths[v] = cur;
			for (auto [u, id] : adj[v]) {
				if (u == from) continue;
				cur[id].flip();
				findBase(u, v, cur);
				cur[id].flip();
	}}}

	//cycle must be constrcuted from base
	bool isCycle(cycle cur) {
		if (cur.none()) return false;
		init(sz(adj)); // union find @\sourceref{datastructures/unionFind.cpp}@
		for (int i = 0; i < sz(edges); i++) {
			if (cur[i]) {
				cur[i] = false;
				if (findSet(edges[i].first) ==
				    findSet(edges[i].second)) break;
				unionSets(edges[i].first, edges[i].second);
		}}
		return cur.none();
	};

	int count() {
		findBase();
		int res = 0;
		for (int i = 1; i < (1 << sz(base)); i++) {
			cycle cur;
			for (int j = 0; j < sz(base); j++) {
				if (((i >> j) & 1) != 0) cur ^= base[j];
			if (isCycle(cur)) res++;
		}
		return res;
	}
};
