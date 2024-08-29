// input: undirected (un)weighted tree as
//        adjacency list containing pair<neighbour,weight>s
//        (To remove weights, remove every "w" and fix errors)
// output[r] = dp[r], where dp[v] :=
//  fin(Sum_{child c of v, regarding root r} from_child( dp[c] ))
struct Reroot {
    using D = todo; // dp value
    using A = todo (often D); // value from a vertex's child(ren)
                              // (A,agg,e) commutative monoid

    A e = todo;
    A from_child(z v, z c, auto w, D dp_c) { todo }
    static A agg(A a, A b) { todo }
    D fin(z v, A chils_agg) { todo }

    vector<D> dp;

    D dfs0(z v, z p, auto& g) {
        A ca = e;
        for(auto [c, w] : g[v]) if(c-p) {
            ca = agg(ca, from_child(v, c, w, dfs0(c, v, g)));
        }
        return dp[v] = fin(v, ca);
    }
    void dfs1(z v, z p, auto& g) {
        vector ps = {e};
        for(auto [c, w] : g[v]) {
            ps.push_back(from_child(v, c, w, dp[c]));
        }
        auto ss = ps;
        exclusive_scan(ps.begin(), ps.end(), ps.begin(), e, agg);
        exclusive_scan(ss.rbegin(),ss.rend(),ss.rbegin(),e, agg);
        z i = 0;
        for(auto [c, w] : g[v]) if(++i, c-p) {
            dp[v] = fin(v, agg(ss[i], ps[i]));
            dfs1(c, v, g);
        }
        dp[v] = fin(v, s[0]);
    }

    auto solve(auto g) {
        dp.resize(sz(g));
        dfs0(0, 0, g);
        dfs1(0, 0, g);
        return dp;
    }
};