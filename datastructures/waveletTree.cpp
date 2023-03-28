struct WaveletTree {
	using it = vector<ll>::iterator;
	WaveletTree *ln, *rn;
	ll lo, hi;
	vector<int> b;
private:
	WaveletTree(it from, it to, ll x, ll y)
	: ln(nullptr), rn(nullptr), lo(x), hi(y), b(1) {
		ll mid = (lo + hi) / 2;
		auto f = [&](ll x){return x < mid;};
		for (it c = from; c != to; c++) {
			b.push_back(b.back() + f(*c));
		}
		if (lo + 1 >= hi || from == to) return;
		it pivot = stable_partition(from, to, f);
		ln = new WaveletTree(from, pivot, lo, mid);
		rn = new WaveletTree(pivot, to, mid, hi);
	}
public:
	WaveletTree(vector<ll> in) : WaveletTree(all(in), 
		*min_element(all(in)), *max_element(all(in)) + 1){}

	// kth element in sort[l, r) all 0-indexed
	ll kth(int l, int r, int k) {
		if (l >= r || k >= r - l) return -1;
		if (lo + 1 >= hi) return lo;
		int inLeft = b[r] - b[l];
		if (k < inLeft) {
			return ln->kth(b[l], b[r], k);
		} else {
			return rn->kth(l-b[l], r-b[r], k-inLeft);
	}}

	// count elements in[l, r) smaller than k
	int countSmaller(int l, int r, ll k) {
		if (l >= r || k <= lo) return 0;
		if (hi <= k) return r - l;
		return ln->countSmaller(b[l], b[r], k) + 
		       rn->countSmaller(l-b[l], r-b[r], k);
	}

	~WaveletTree(){
		delete ln;
		delete rn;
	}
};
