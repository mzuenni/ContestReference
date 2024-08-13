struct Line {
	mutable ll m, c, p;
	bool operator<(const Line& o) const {return m < o.m;}
	bool operator<(ll x) const {return p < x;}
};

struct HullDynamic : multiset<Line, less<>> { // max über Geraden
	// (for doubles, use INF = 1/.0, div(a,c) = a/c)
	ll div(ll a, ll c) {return a / c - ((a ^ c) < 0 && a % c);}

	bool isect(iterator x, iterator y) {
		if (y == end()) {x->p = INF; return false;}
		if (x->m == y->m) x->p = x->c > y->c ? INF : -INF;
		else x->p = div(y->c - x->c, x->m - y->m);
		return x->p >= y->p;
	}

	void add(ll m, ll c) {
		auto x = insert({m, c, 0});
		while (isect(x, next(x))) erase(next(x));
		if (x != begin()) {
			x--;
			if (isect(x, next(x))) {
				erase(next(x));
				isect(x, next(x));
		}}
		while (x != begin() && prev(x)->p >= x->p) {
			x--;
			isect(x, erase(next(x)));
	}}

	ll query(ll x) {
		auto l = *lower_bound(x);
		return l.m * x + l.c;
	}
};
