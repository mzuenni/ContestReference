struct SparseTable {
	vector<vector<int>> st;
	vector<ll> *a;

	bool better(int lidx, int ridx) {
		return a->at(lidx) <= a->at(ridx);
	}

	void init(vector<ll> *vec) {
		a = vec;
		st.assign(__lg(sz(*a)) + 1, vector<int>(sz(*a)));
		for (int i = 0; i < sz(*a); i++) st[0][i] = i;
		for (int j = 0; (2 << j) <= sz(*a); j++) {
			for (int i = 0; i + (2 << j) <= sz(*a); i++) {
				st[j + 1][i] = better(st[j][i] , st[j][i + (1 << j)])
				                    ? st[j][i] : st[j][i + (1 << j)];
	}}}

	int queryIdempotent(int l, int r) {
		int j = __lg(r - l); //31 - builtin_clz(r - l);
		return better(st[j][l] , st[j][r - (1 << j)])
		            ? st[j][l] : st[j][r - (1 << j)];
	}
};