struct DisjointST {
	static constexpr ll neutral = 0;
	vector<vector<ll>> dst;
	ll* a;

	ll combine(const ll& x, const ll& y) {
		return x + y;
	}

	void init(vector<ll>* vec) {
		int n = sz(*vec);
		a = vec->data();
		dst.assign(__lg(n) + 1, vector<ll>(n + 1, neutral));
		for (int h = 0, l = 1; l <= n; h++, l *= 2) {
			for (int c = l; c < n + l; c += 2 * l) {
				for (int i = c; i < min(n, c + l); i++)
					dst[h][i + 1] = combine(dst[h][i], vec->at(i));
				for (int i = min(n, c); i > c - l; i--)
					dst[h][i - 1] = combine(vec->at(i - 1), dst[h][i]);
	}}}

	ll query(int l, int r) {
		if (r <= l) return neutral;
		int h = __lg(l ^ r);
		return combine(dst[h][l], dst[h][r]);
	}
};
