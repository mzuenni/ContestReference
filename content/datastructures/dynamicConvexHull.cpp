struct Line {
	mutable ll m, b, p;
	bool operator<(const Line& o) const {return m < o.m;}
	bool operator<(ll x) const {return p < x;}
};

struct HullDynamic : multiset<Line, less<>> { // max über Geraden
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	ll div(ll a, ll b) {return a / b - ((a ^ b) < 0 && a % b);}

	bool isect(iterator x, iterator y) {
		if (y == end()) {x->p = INF; return false;}
		if (x->m == y->m) x->p = x->b > y->b ? INF : -INF;
		else x->p = div(y->b - x->b, x->m - y->m);
		return x->p >= y->p;
	}

	void add(ll m, ll b) {
		auto x = insert({m, b, 0});
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
		return l.m * x + l.b;
	}
};
