int h; // = __lg(2*n)
//a neutral value for the update:
constexpr ll updateFlag = 0;
vector<ll> d(N, updateFlag);

void apply(int p, ll value) {
	tree[p] += value;
	if (p < sz(tree)/2) d[p] += value;
}

void build(int p) {
	p >>= __builtin_ctzll(p);
	while (p > 1) {
		p/=2;
		tree[p] = max(tree[2*p], tree[2*p+1]) + d[p];
}}

void push(int p) {
	for (int s = h; s > 0; s--) {
		int i = p >> s;
		if (d[i] != updateFlag) {
			apply(2*i  , d[i]);
			apply(2*i+1, d[i]);
			d[i] = updateFlag;
}}}

void update(int l, int r, ll value) { // add value
	l += sz(tree)/2, r += sz(tree)/2;
	int l0 = l, r0 = r;
	for (; l < r; l /= 2, r /= 2) {
		if (l&1) apply(l++, value);
		if (r&1) apply(--r, value);
	}
	build(l0);
	build(r0 - 1);
}

ll query(int l, int r) { // max(l..r)
	l += sz(tree)/2, r += sz(tree)/2;
	push(l);
	push(r - 1);
	ll res = query_default;
	for (; l < r; l /= 2, r /= 2) {
		if (l&1) res = max(res, tree[l++]);
		if (r&1) res = max(tree[--r], res);
	}
	return res;
}

