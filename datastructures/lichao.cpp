vector<ll> xs; // IMPORTANT: Initialize before constructing Lichao!

struct Fun{ // Default: Linear function. Change it to needed function type. 
    ll m, c;
    ll operator()(int x){
        return m*xs[x] + c;
    }
};

// Default: Computes min. Change lines with comment for max.
struct Lichao{
    const Fun id = {0, inf}; // {0, -inf}
    int n, cap;
    vector<Fun> seg;
    Lichao(){
        n = sz(xs);
        for(cap = 1; cap < n; cap *= 2);
        seg.assign(2*cap, id);
    }
    void myInsert(Fun f, int l, int r, int i){
        while(i < 2*cap){
            int m = (l+r)/2;
            if(m >= n) {r = m; i = 2*i; continue;}
            Fun &g = seg[i];
            if(f(m) < g(m)) swap(f, g); // >
            if(f(l) < g(l)) r = m, i = 2*i; // >
            else l = m, i = 2*i+1;
        }
    }
    void mySegmentInsert(Fun f, int l, int r, int a, int b, int i){
        if(l <= a && b <= r) myInsert(f, a, b, i);
        else if(a < r && l < b){
            int m = (a+b)/2;
            mySegmentInsert(f, l, r, a, m, 2*i);
            mySegmentInsert(f, l, r, m, b, 2*i+1);
        }
    }
    void insert(Fun f){myInsert(f, 0, cap, 1);}
    void segmentInsert(Fun f, ll l, ll r){
        mySegmentInsert(f, lower_bound(all(xs), l)-xs.begin(), lower_bound(all(xs), r)-xs.begin(), 0, cap, 1);
    }
    ll myQuery(int x){
        int i = x+cap;
        ll ans = seg[i](x);
        while(i > 1) ans = min(ans, seg[i/=2](x)); // max
        return ans;
    }
    ll query(ll x){return myQuery(lower_bound(all(xs),x)-xs.begin());}
};
