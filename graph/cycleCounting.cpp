constexpr int maxEdges = 128;
using cycle = bitset<maxEdges>;
struct cylces {
	vector<vector<pair<int, int>>> adj;
	vector<bool> seen;
	vector<cycle> paths, base;
	vector<pair<int, int>> edges;

	cylces(int n) : adj(n), seen(n), paths(n) {}

	void addEdge(int a, int b) {
		adj[a].push_back({b, sz(edges)});
		adj[b].push_back({a, sz(edges)});
		edges.push_back({a, b});
	}

	void addBase(cycle cur) {
		for (cycle o : base) {
			o ^= cur;
			if (o._Find_first() > cur._Find_first()) cur = o;
		}
		if (cur.any()) base.push_back(cur);
	}

	void findBase(int c = 0, int p = -1, cycle cur = {}) {
		if (adj.empty()) return;
		if (seen[c]) {
			addBase(cur ^ paths[c]);
		} else {
			seen[c] = true;
			paths[c] = cur;
			for (auto e : adj[c]) {
				if (e.first == p) continue;
				cur[e.second].flip();
				findBase(e.first, c, cur);
				cur[e.second].flip();
	}}}

	//cycle must be constrcuted from base
	bool isCycle(cycle cur) {
		if (cur.none()) return false;
		init(sz(adj)); // union find
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
