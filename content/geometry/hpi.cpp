constexpr ll INF = 0x1FFF'FFFF'FFFF'FFFF; //THIS CODE IS WIP

bool left(pt p) {return real(p) < 0 || 
					   (real(p) == 0 && imag(p) < 0);}
struct hp {
	pt from, to;

	hp(pt a, pt b) : from(a), to(b) {}
	hp(pt dummy) : hp(dummy, dummy) {}

	bool dummy() const {return from == to;}
	pt dir() const {return dummy() ? to : to - from;}
	bool operator<(const hp& o) const {
		if (left(dir()) != left(o.dir())) 
			return left(dir()) > left(o.dir());
		return cross(dir(), o.dir()) > 0;
	}

	using lll = __int128;
	using ptl = complex<lll>;
	ptl mul(lll m, ptl p) const {return m*p;}//ensure 128bit

	bool check(const hp& a, const hp& b) const {
		if (dummy() || b.dummy()) return false;
		if (a.dummy()) {
			ll ort = sgn(cross(b.dir(), dir()));
			if (ort == 0) return cross(from, to, a.from) < 0;
			return cross(b.dir(), a.dir()) * ort > 0;
		}
		ll x = cross(a.dir(), b.dir());
		ll y = cross(b.from - a.from, b.dir());
		ptl i = mul(x, a.from) + mul(y, a.dir()); //intersect a and b
		// check if i is outside/right of this
		return imag(conj(mul(sgn(x),dir()))*(i-mul(x,from))) < 0;
	}
};

constexpr ll lim = 2e9+7;

deque<hp> intersect(vector<hp> hps) {
	hps.push_back(hp(pt{lim + 1, -1}));
	hps.push_back(hp(pt{lim + 1, 1}));
	sort(all(hps));

	deque<hp> dq = {hp(pt{-lim - 1, 1})};
	for (auto x : hps) {
		while (sz(dq) > 1 && x.check(dq.end()[-1], dq.end()[-2]))
			dq.pop_back();
		while (sz(dq) > 1 && x.check(dq[0], dq[1]))
			dq.pop_front();

		if (cross(x.dir(), dq.back().dir()) == 0) {
			if (dot(x.dir(), dq.back().dir()) < 0) return {};
			if (cross(x.from, x.to, dq.back().from) < 0)
				dq.pop_back();
			else continue;
		}
		dq.push_back(x);
	}

	while (sz(dq) > 2 && dq[0].check(dq.end()[-1], dq.end()[-2]))
		dq.pop_back();
	while (sz(dq) > 2 && dq.back().check(dq[0], dq[1]))
		dq.pop_front();

	if (sz(dq) < 3) return {};
	return dq;
}
