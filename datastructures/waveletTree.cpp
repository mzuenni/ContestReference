struct WaveletTree {
	using it = vector<ll>::iterator;
	WaveletTree *ln = nullptr, *rn = nullptr;
	vector<int> b = {0};
	ll lo, hi;

	WaveletTree(vector<ll> a) : WaveletTree(all(a), // call this
		*min_element(all(a)), *max_element(all(a)) + 1) {}

	WaveletTree(it from, it to, ll x, ll y) : lo(x), hi(y) {
		if (lo + 1 >= hi || from == to) return;
		ll mid = (lo + hi) / 2;
		auto f = [&](ll x){return x < mid;};
		for (it c = from; c != to; c++) {
			b.push_back(b.back() + f(*c));
		}
		it pivot = stable_partition(from, to, f);
		ln = new WaveletTree(from, pivot, lo, mid);
		rn = new WaveletTree(pivot, to, mid, hi);
	}

	// kth element in sort[l, r) all 0-indexed
	ll kth(int l, int r, int k) {
		if (l >= r || k >= r - l) return -1;
		if (lo + 1 >= hi) return lo;
		int inLeft = b[r] - b[l];
		if (k < inLeft) return ln->kth(b[l], b[r], k);
		else return rn->kth(l-b[l], r-b[r], k-inLeft);
	}

	// count elements in[l, r) smaller than k
	int countSmaller(int l, int r, ll k) {
		if (l >= r || k <= lo) return 0;
		if (hi <= k) return r - l;
		return ln->countSmaller(b[l], b[r], k) +
		       rn->countSmaller(l-b[l], r-b[r], k);
	}

	~WaveletTree() {delete ln; delete rn;}
};
