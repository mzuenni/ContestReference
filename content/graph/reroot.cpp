// output[r] = dp[r], where dp[v] :=
//  fin(Sum_{child c of v, regarding root r} fromChild( dp[c] ))

// To remove weights, remove every "w" and "W" and fix errors
struct Reroot {
  using D = /*todo*/; // dp value
  using A = /*todo(often D)*/; //value from a vertex's child(ren)
                               //(A,agg,e) commutative monoid

  A e = /*todo*/;
  A fromChild(int v, int c, auto w, D dp_c) { /*todo*/ }
  static A agg(A a, A b) { /*todo*/ }
  D fin(int v, A chilsAgg) { /*todo*/ }

  vector<D> dp;

  D dfs0(auto& g, int v, int from = -1) {
    A ca = e;
    for (auto [c, w] : g[v]) {
      if (c == from) continue;
      ca = agg(ca, fromChild(v, c, w, dfs0(c, v, g)));
    }
    return dp[v] = fin(v, ca);
  }

  void dfs1(auto& g, int v, int from = -1) {
    vector ps = {e};
    for (auto [c, w] : g[v]) {
      ps.push_back(fromChild(v, c, w, dp[c]));
    }
    auto ss = ps;
    exclusive_scan(be(ps), ps.begin(), e, agg);
    exclusive_scan(ss.rbegin(), ss.rend(), ss.rbegin(), e, agg);
    int i = 0;
    for (auto [c, w] : g[v]) {
      ++i;
      if (c == from) continue;
      dp[v] = fin(v, agg(ss[i], ps[i]));
      dfs1(c, v, g);
    }
    dp[v] = fin(v, ss[0]);
  }

  template<typename W>
  auto solve(vector<vector<pair<int, W>>> g) {
    dp.resize(sz(g));
    dfs0(g, 0);
    dfs1(g, 0);
    return dp;
  }
};