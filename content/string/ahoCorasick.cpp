constexpr ll ALPHABET_SIZE = 26, OFFSET = 'a';
struct AhoCorasick {
	struct vert {
		int suffix = 0, ch, cnt = 0;
		array<int, ALPHABET_SIZE> nxt = {};

		vert(int p, int c) : suffix(-p), ch(c) {fill(all(nxt), -1);}
	};
	vector<vert> aho = {{0, -1}};

	int addString(string &s) {
		int v = 0;
		for (auto c : s) {
			int idx = c - OFFSET;
			if (aho[v].nxt[idx] == -1) {
				aho[v].nxt[idx] = sz(aho);
				aho.emplace_back(v, idx);
			}
			v = aho[v].nxt[idx];
		}
		aho[v].cnt++;
		return v; // trie node index of pattern (pattern state)
	}

	int getSuffix(int v) {
		if (aho[v].suffix < 0) {
			aho[v].suffix = go(getSuffix(-aho[v].suffix), aho[v].ch);
		}
		return aho[v].suffix;
	}

	int go(int v, int idx) { // Root is v=0, idx is char - OFFSET
		if (aho[v].nxt[idx] != -1) return aho[v].nxt[idx];
		return v == 0 ? 0 : aho[v].nxt[idx] = go(getSuffix(v), idx);
	}

	vector<vector<int>> adj;
	vector<ll> dp;
	void buildGraph() {
		adj.resize(sz(aho));
		dp.assign(sz(aho), 0);
		for (int i = 1; i < sz(aho); i++) {
			adj[getSuffix(i)].push_back(i);
	}}

	void dfs(int v = 0) { // dp on tree
		for (int u : adj[v]) {
			//dp[u] = dp[v] + aho[u].cnt; // pattern count
			dfs(u);
			dp[v] += dp[u]; // no of matches
	}}
};
