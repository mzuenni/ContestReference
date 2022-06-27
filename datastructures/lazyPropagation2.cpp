void calc(int p, ll k) {
	if (d[p] == updateFlag) tree[p] = tree[2*p] + tree[2*p+1];
	else tree[p] = d[p] * k;
}

void apply(int p, ll value, int k) {
	tree[p] = value * k;
	if (p < sz(tree)/2) d[p] = value;
}

void build(int l, int r) {
	int k = 2;
	for (l += sz(tree)/2, r += sz(tree)/2-1; l > 1; k <<= 1) {
		l/=2, r/=2;
		for (int i = r; i >= l; --i) calc(i, k);
}}

void push(int l, int r) {
	int s = h, k = 1 << (h-1);
	for (l += sz(tree)/2, r += sz(tree)/2-1; s > 0; --s, k/=2) {
		for (int i = l >> s; i <= r >> s; ++i) {
			if (d[i] != updateFlag) {
				apply(2*i  , d[i], k);
				apply(2*i+1, d[i], k);
				d[i] = updateFlag;
}}}}

void modify(int l, int r, ll value) {
	if (value == updateFlag) return;
	push(l, l + 1);
	push(r - 1, r);
	int l0 = l, r0 = r, k = 1;
	for (l += sz(tree)/2, r += sz(tree)/2; l<r; l/=2, r/=2, k*=2) {
		if (l&1) apply(l++, value, k);
		if (r&1) apply(--r, value, k);
	}
	build(l0, l0 + 1);
	build(r0 - 1, r0);
}

ll query(int l, int r) {
	push(l, l + 1);
	push(r - 1, r);
	ll res = query_default;
	for (l += sz(tree)/2, r += sz(tree)/2; l < r; l/=2, r/=2) {
		if (l&1) res += tree[l++];
		if (r&1) res += tree[--r];
	}
	return res;
}
