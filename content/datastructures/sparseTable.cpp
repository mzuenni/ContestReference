struct SparseTable {
	vector<vector<int>> st;
	ll *a;

	int better(int lidx, int ridx) {
		return a[lidx] <= a[ridx] ? lidx : ridx;
	}

	void init(vector<ll> *vec) {
		int n = sz(*vec);
		a = vec->data();
		st.assign(__lg(n) + 1, vector<int>(n));
		iota(all(st[0]), 0);
		for (int j = 0; (2 << j) <= n; j++) {
			for (int i = 0; i + (2 << j) <= n; i++) {
				st[j + 1][i] = better(st[j][i] , st[j][i + (1 << j)]);
	}}}

	int queryIdempotent(int l, int r) {
		int j = __lg(r - l); //31 - builtin_clz(r - l);
		return better(st[j][l] , st[j][r - (1 << j)]);
	}
};
