mt19937 rng(0xc4bd5dad);
struct Treap {
	struct Node {
		ll val;
		int prio, size = 1, l = -1, r = -1;
		Node(ll x) : val(x), prio(rng()) {}
	};

	vector<Node> treap;
	int root = -1;

	int getSize(int v) {
		return v < 0 ? 0 : treap[v].size;
	}

	void upd(int v) {
		if (v < 0) return;
		auto& V = treap[v];
		V.size = 1 + getSize(V.l) + getSize(V.r);
		// Update Node Code
	}

	void push(int v) {
		if (v < 0) return;
		//auto& V = treap[v];
		//if (V.lazy) {
		//	Lazy Propagation Code
		//	if (V.l >= 0) treap[V.l].lazy = true;
		//	if (V.r >= 0) treap[V.r].lazy = true;
		//	V.lazy = false;
		//}
	}

	pair<int, int> split(int v, int k) {
		if (v < 0) return {-1, -1};
		auto& V = treap[v];
		push(v);
		if (getSize(V.l) >= k) { // "V.val >= k" for lower_bound(k)
			auto [left, right] = split(V.l, k);
			V.l = right;
			upd(v);
			return {left, v};
		} else {
			// and only "k"
			auto [left, right] = split(V.r, k - getSize(V.l) - 1);
			V.r = left;
			upd(v);
			return {v, right};
	}}

	int merge(int left, int right) {
		if (left < 0) return right;
		if (right < 0) return left;
		if (treap[left].prio < treap[right].prio) {
			push(left);
			treap[left].r = merge(treap[left].r, right);
			upd(left);
			return left;
		} else {
			push(right);
			treap[right].l = merge(left, treap[right].l);
			upd(right);
			return right;
	}}

	void insert(int i, ll val) { // and i = val
		auto [left, right] = split(root, i);
		treap.emplace_back(val);
		left = merge(left, sz(treap) - 1);
		root = merge(left, right);
	}

	void remove(int i, int count = 1) {
		auto [left, t_right] = split(root, i);
		auto [middle, right] = split(t_right, count);
		root = merge(left, right);
	}
	// for query use remove and read middle BEFORE remerging
};
