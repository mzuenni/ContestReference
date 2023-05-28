template<typename T = ll, typename U = ll>
struct SegTree {
	int size, height;
	static constexpr T neutral = 0; // Neutral element for combine
	static constexpr U updateFlag = 0; // Unused value by updates
	vector<T> tree; vector<U> lazy;

	SegTree(const vector<T>& a) : SegTree(sz(a)) {
		copy(all(a), tree.begin() + size);
		for (int i = size - 1; i > 0; i--)
			tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
	}

	SegTree(int n) : size(n), height(__lg(2 * n)),
		tree(2 * n, neutral), lazy(n, updateFlag) {}

	T combine(T a, T b) {return a + b;} // Modify this + neutral

	void apply(int i, U val, int k) { // And this + updateFlag
		tree[i] = val * k;
		if (i < size) lazy[i] = val; // Don't forget this
	}

	void push_down(int i, int k) {
		if (lazy[i] != updateFlag) {
			apply(2 * i, lazy[i], k);
			apply(2 * i + 1, lazy[i], k);
			lazy[i] = updateFlag;
	}}

	void push(int i) {
		for (int s = height, k = 1 << (height-1); s > 0; s--, k /= 2)
			push_down(i >> s, k);
	}

	void build(int i) {
		for (int k = 2; i /= 2; k *= 2) {
			push_down(i, k / 2);
			tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
	}}

	void update(int l, int r, U val) { // data[l..r) = val
		l += size, r += size;
		int l0 = l, r0 = r;
		push(l0), push(r0 - 1);
		for (int k = 1; l < r; l /= 2, r /= 2, k *= 2) {
			if (l&1) apply(l++, val, k);
			if (r&1) apply(--r, val, k);
		}
		build(l0), build(r0 - 1);
	}

	T query(int l, int r) { // sum[l..r)
		l += size, r += size;
		push(l), push(r - 1);
		T resL = neutral, resR = neutral;
		for (; l < r; l /= 2, r /= 2) {
			if (l&1) resL = combine(resL, tree[l++]);
			if (r&1) resR = combine(tree[--r], resR);
		}
		return combine(resL, resR);
	}

	// Optional:
	ll lower_bound(int l, int r, T x) {
		l += size, r += size;
		push(l), push(r - 1);
		vector<pair<int, int>> a, st;
		for (int k = 1; l < r; l /= 2, r /= 2, k *= 2) {
			if (l&1) a.emplace_back(l++, k);
			if (r&1) st.emplace_back(--r, k);
		}
		a.insert(a.end(), st.rbegin(), st.rend());
		for (auto [i, k] : a) {
			if (tree[i] >= x) return find(i, x, k); // Modify this
		}
		return -1;
	}

	ll find(int i, T x, int k) {
		if (i >= size) return i - size;
		push_down(i, k / 2);
		if (tree[2*i] >= x) return find(2 * i, x, k / 2); // And this
		else return find(2 * i + 1, x, k / 2);
	}
};
