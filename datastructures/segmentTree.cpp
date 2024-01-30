struct SegTree {
	using T = ll;
	int n;
	vector<T> tree;
	static constexpr T E = 0; // Neutral element for combine

	SegTree(vector<T>& a) : n(sz(a)), tree(2 * n) {
	//SegTree(int size, T val = E) : n(size), tree(2 * n, val) {
		copy(all(a), tree.begin() + n);
		for (int i = n - 1; i > 0; i--) { // remove for range update
			tree[i] = comb(tree[2 * i], tree[2 * i + 1]);
	}}

	ll comb(T a, T b) {return a + b;} // modify this + neutral

	void update(int i, T val) {
		tree[i += n] = val; // apply update code
		while (i /= 2) tree[i] = comb(tree[2 * i], tree[2 * i + 1]);
	}

	T query(int l, int r) {
		T resL = E, resR = E;
		for (l += n, r += n; l < r; l /= 2, r /= 2) {
			if (l&1) resL = comb(resL, tree[l++]);
			if (r&1) resR = comb(tree[--r], resR);
		}
		return comb(resL, resR);
	}

	// OR: range update + point query, needs commutative comb
	void modify(int l, int r, T val) {
		for (l += n, r += n; l < r; l /= 2, r /= 2) {
			if (l&1) tree[l] = comb(tree[l], val), l++;
			if (r&1) --r, tree[r] = comb(tree[r], val);
	}}

	T query(int i) {
		T res = E;
		for (i += n; i > 0; i /= 2) res = comb(res, tree[i]);
		return res;
	}
};
