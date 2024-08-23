struct seg {
	pt a, b;
	int id;
	bool operator<(const seg& o) const {
		if (real(a) < real(o.a)) {
			int s = ccw(a, b, o.a);
			return (s > 0 || (s == 0 && imag(a) < imag(o.a)));
		} else if (real(a) > real(o.a)) {
			int s = ccw(o.a, o.b, a);
			return (s < 0 || (s == 0 && imag(a) < imag(o.a)));
		}
		return imag(a) < imag(o.a);
	}
};

struct event {
	pt p;
	int id, type;
	bool operator<(const event& o) const {
		if (real(p) != real(o.p)) return real(p) < real(o.p);
		if (imag(p) != imag(o.p)) return imag(p) < imag(o.p);
		return type > o.type;
	}
};

bool lessPT(const pt& a, const pt& b) {
	return real(a) != real(b) ? real(a) < real(b)
	                          : imag(a) < imag(b);
}

bool intersect(const seg& a, const seg& b) {
	return segmentIntersection(a.a, a.b, b.a, b.b); //@\sourceref{geometry/linesAndSegments.cpp}@
}

pair<int, int> intersect(vector<seg>& segs) {
	vector<event> events;
	for (seg& s : segs) {
		if (lessPT(s.b, s.a)) swap(s.b, s.a);
		events.push_back({s.a, s.id, 1});
		events.push_back({s.b, s.id, -1});
	}
	sort(all(events));

	set<seg> q;
	vector<set<seg>::iterator> where(sz(segs));
	for (auto e : events) {
		int id = e.id;
		if (e.type > 0) {
			auto it = q.lower_bound(segs[id]);
			if (it != q.end() && intersect(*it, segs[id]))
				return {it->id, segs[id].id};
			if (it != q.begin() && intersect(*prev(it), segs[id]))
				return {prev(it)->id, segs[id].id};
			where[id] = q.insert(it, segs[id]);
		} else {
			auto it = where[id];
			if (it != q.begin() && next(it) != q.end() && intersect(*next(it), *prev(it)))
				return {next(it)->id, prev(it)->id};
			q.erase(it);
		}
	}
	return {-1, -1};
}
