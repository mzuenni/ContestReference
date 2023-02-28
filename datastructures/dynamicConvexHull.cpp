struct Line {
	mutable ll m, b, p;
	bool operator<(const Line& o) const { return m < o.m; }
	bool operator<(ll x) const { return p < x; }
};

struct HullDynamic : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static constexpr ll INF = LLONG_MAX;
	ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }

	bool isect(iterator x, iterator y) {
		if (y == end()) {x->p = INF; return false;}
		if (x->m == y->m) x->p = x->b > y->b ? INF : -INF;
		else x->p = div(y->b - x->b, x->m - y->m);
		return x->p >= y->p;
	}

	void add(ll m, ll b) {
		auto z = insert({m, b, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}

	ll query(ll x) {
		auto l = *lower_bound(x);
		return l.m * x + l.b;
	}
};
