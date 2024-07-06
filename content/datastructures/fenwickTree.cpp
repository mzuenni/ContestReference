vector<ll> tree;

void update(int i, ll val) {
	for (i++; i < sz(tree); i += i & -i) tree[i] += val;
}

void init(int n) {
	tree.assign(n + 1, 0);
}

ll prefix_sum(int i) {
	ll sum = 0;
	for (i++; i > 0; i -= i & -i) sum += tree[i];
	return sum;
}
