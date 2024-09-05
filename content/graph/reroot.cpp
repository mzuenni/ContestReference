using W = ll; // edge weight type
vector<vector<pair<int, W>>> adj;

struct Reroot {
	using T = ll; // dp type

	static constexpr T E = 0; // neutral element
	T takeChild(int v, int c, W w, T x) {} // move child along edge
	static T comb(T x, T y) {}
	T fin(int v, T x) {} // add v to own dp value x

	vector<T> dp;

	T dfs0(int v, int from = -1) {
		T val = E;
		for (auto [u, w] : adj[v]) {
			if (u == from) continue;
			val = comb(val, takeChild(v, u, w, dfs0(u, v)));
		}
		return dp[v] = fin(v, val);
	}

	void dfs1(int v, int from = -1) {
		vector<T> pref = {E};
		for (auto [u, w] : adj[v]) {
			pref.push_back(takeChild(v, u, w, dp[u]));
		}
		auto suf = pref;
		partial_sum(all(pref), pref.begin(), comb);
		exclusive_scan(suf.rbegin(), suf.rend(),
		               suf.rbegin(), E, comb);

		for (int i = 0; i < sz(adj[v]); i++) {
			auto [u, w] = adj[v][i];
			if (u == from) continue;
			dp[v] = fin(v, comb(pref[i], suf[i + 1]));
			dfs1(u, v);
		}
		dp[v] = fin(v, suf[0]);
	}

	auto solve() {
		dp.assign(sz(adj), E);
		dfs0(0);
		dfs1(0);
		return dp;
	}
};
