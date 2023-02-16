vector<ll> tree;
constexpr ll neutral = 0; // Neutral element for combine

ll combine(ll a, ll b) {
	return a + b;
}

void init(vector<ll>& a) {
	tree.assign(2 * sz(a), 0);
	copy(all(a), tree.begin() + sz(a));
	for (int i = sz(tree)/2 - 1; i > 0; i--) {
		tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
}}

void update(int i, ll val) {
	for (tree[i += sz(tree)/2] = val; i /= 2; ) {
		tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
}}

ll query(int l, int r) {
	ll resL = neutral, resR = neutral;
	for (l += sz(tree)/2, r += sz(tree)/2; l < r; l /= 2, r /= 2) {
		if (l&1) resL = combine(resL, tree[l++]);
		if (r&1) resR = combine(tree[--r], resR);
	}
	return combine(resL, resR);
}

// Oder: Intervall-Modifikation, Punkt-Query:
void modify(int l, int r, ll val) {
	for (l += sz(tree)/2, r += sz(tree)/2; l < r; l /= 2, r /= 2) {
		if (l&1) {tree[l] = combine(tree[l], val); l++;};
		if (r&1) {--r; tree[r] = combine(tree[r], val);};
}}

ll query(int i) {
	ll res = neutral;
	for (i += sz(tree)/2; i > 0; i /= 2) {
		res = combine(res, tree[i]);
	}
	return res;
}
