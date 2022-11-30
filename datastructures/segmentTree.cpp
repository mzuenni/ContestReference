vector<ll> tree;
constexpr ll query_default = 0;

ll combine(ll a, ll b) {
	return a + b;
}

void init(vector<ll>& values) {
	tree.assign(sz(values)*2, 0);
	copy(all(values), tree.begin() + sz(values));
	for (int i = sz(tree)/2 - 1; i > 0; --i) {
		tree[i] = combine(tree[2*i], tree[2*i+1]);
}}

void update(int p, ll value) {
	for (tree[p += sz(tree)/2] = value, p /= 2; p > 0; p /= 2) {
		tree[p] = combine(tree[2*p], tree[2*p+1]);
}}

ll query(int l, int r) {
	ll resL = query_default;
	ll resR = query_default;
	for (l += sz(tree)/2, r += sz(tree)/2; l < r; l /= 2, r /= 2) {
		if (l&1) resL = combine(resL, tree[l++]);
		if (r&1) resR = combine(tree[--r], resR);
	}
	return combine(resL, resR);
}

// Oder: Intervall-Modifikation, Punkt-Query:
void modify(int l, int r, ll value) {
	for (l += sz(tree)/2, r += sz(tree)/2; l < r; l /= 2, r /= 2) {
		if (l&1) {tree[l] = combine(tree[l], value); l++;};
		if (r&1) {--r; tree[r] = combine(value, tree[r]);};
}}

ll query(int p) {
	ll res = query_default;
	for (p += sz(tree)/2; p > 0; p = p/2) {
		res = combine(res, tree[p]);
	}
	return res;
}
