// Usual Tree DP can be broken down in 4 steps:
// - Initialize dp[v] = identity
// - Iterate over all children w and take a value for w 
//   by looking at dp[w] and possibly the edge label of v -> w
// - combine the values of those children
//   usually, this operation should be commutative and associative
// - finalize the value of dp[v] after iterating over all children
struct Reroot{
	using T = ll;

	// identity element
	T E(){}
	// x: dp value of child
	// e: index of edge going to child
	T takeChild(T x, int e){}
	T combine(T x, T y){}
	// called after combining all dp values of children
	T finalize(T x, int v){}

	vector<vector<pair<int, int>>> g;
	vector<int> ord, pae;
	vector<T> dp;

	T dfs(int v){
		ord.push_back(v);
		for(auto [w, e] : g[v]){
			g[w].erase(find(all(g[w]), pair(v, e^1)));
			pae[w] = e^1;
			dp[v] = combine(dp[v], takeChild(dfs(w), e));
		}
		return dp[v] = finalize(dp[v], v);
	}

	vector<T> solve(int n, vector<pair<int, int>> edges){
		g.resize(n);
		for(int i = 0; i < n-1; i++){
			g[edges[i].first].emplace_back(edges[i].second, 2*i);
			g[edges[i].second].emplace_back(edges[i].first, 2*i+1);
		}
		pae.assign(n, -1);
		dp.assign(n, E());
		dfs(0);
		vector<T> updp(n, E()), res(n, E());
		for(int v : ord){
			vector<T> pref(sz(g[v])+1), suff(sz(g[v])+1);
			if(v != 0) pref[0] = takeChild(updp[v], pae[v]);
			for(int i = 0; i < sz(g[v]); i++){
				pref[i+1] = suff[i] = takeChild(dp[g[v][i].first], g[v][i].second);
				pref[i+1] = combine(pref[i], pref[i+1]);
			}
			for(int i = sz(g[v])-1; i >= 0; i--)
				suff[i] = combine(suff[i], suff[i+1]);
			for(int i = 0; i < sz(g[v]); i++)
				updp[g[v][i].first] = finalize(combine(pref[i], suff[i+1]), v);
			res[v] = finalize(pref.back(), v);
		}
		return res;
	}
};