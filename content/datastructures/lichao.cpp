vector<ll> xs; // IMPORTANT: Initialize before constructing!
int findX(int i) {return lower_bound(all(xs), i) - begin(xs);}

struct Fun { // Default: Linear function. Change as needed. 
	ll m, c;
	ll operator()(int x) {return m*xs[x] + c;}
};

// Default: Computes min. Change lines with comment for max.
struct Lichao {
	static constexpr Fun id = {0, inf}; // {0, -inf}
	int n, cap;
	vector<Fun> seg;
	Lichao() : n(sz(xs)), cap(2<<__lg(n)), seg(2*cap, id) {}
	
	void _insert(Fun f, int l, int r, int i) {
		while (i < 2*cap){
			int m = (l+r)/2;
			if (m >= n) {r = m; i = 2*i; continue;}
			Fun &g = seg[i];
			if (f(m) < g(m)) swap(f, g); // >
			if (f(l) < g(l)) r = m, i = 2*i; // >
			else l = m, i = 2*i+1;
	}}
	void insert(Fun f) {_insert(f, 0, cap, 1);}

	void _segmentInsert(Fun f, int l, int r, int a, int b, int i) {
		if (l <= a && b <= r) _insert(f, a, b, i);
		else if (a < r && l < b){
			int m = (a+b)/2;
			_segmentInsert(f, l, r, a, m, 2*i);
			_segmentInsert(f, l, r, m, b, 2*i+1);
	}}
	void segmentInsert(Fun f, ll l, ll r) {
		_segmentInsert(f, findX(l), findX(r), 0, cap, 1);
	}

	ll _query(int x) {
		ll ans = inf; // -inf
		for (int i = x + cap; i > 0; i /= 2) {
			ans = min(ans, seg[i](x)); // max
		}
		return ans;
	}
	ll query(ll x) {return _query(findX(x));}
};
