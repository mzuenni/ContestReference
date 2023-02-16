int h; // = __lg(2*n)
//a value that is not used by the update query:
constexpr ll updateFlag = -1;
vector<ll> d(N, updateFlag);

void apply(int p, ll value, int k) {
	tree[p] = value * k;
	if (p < sz(tree)/2) d[p] = value;
}

void build(int p) {
	p >>= __builtin_ctzll(p);
	for (int k = 2; p > 1; k <<= 1) {
		p/=2;
		if (d[p] == updateFlag) tree[p] = tree[2*p] + tree[2*p+1];
		else tree[p] = d[p] * k;
}}

void push(int p) {
	for (int s = h, k = 1 << (h-1); s > 0; s--, k/=2) {
		int i = p >> s;
		if (d[i] != updateFlag) {
			apply(2*i  , d[i], k);
			apply(2*i+1, d[i], k);
			d[i] = updateFlag;
}}}

void update(int l, int r, ll value) { // assign value
	if (value == updateFlag) return;
	l += sz(tree)/2, r += sz(tree)/2;
	push(l);
	push(r - 1);
	int l0 = l, r0 = r, k = 1;
	for (; l < r; l /= 2, r /= 2, k *= 2) {
		if (l&1) apply(l++, value, k);
		if (r&1) apply(--r, value, k);
	}
	build(l0);
	build(r0 - 1);
}

ll query(int l, int r) { // sum(l..r)
	l += sz(tree)/2, r += sz(tree)/2;
	push(l);
	push(r - 1);
	ll res = query_default;
	for (; l < r; l /= 2, r /= 2) {
		if (l&1) res = res + tree[l++];
		if (r&1) res = tree[--r] + res;
	}
	return res;
}
