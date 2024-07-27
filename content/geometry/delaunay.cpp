using lll = __int128;
using pt = complex<lll>;

constexpr pt INF_PT = pt(2e18, 2e18);

bool circ(pt p, pt a, pt b, pt c) {// p in circle(A,B,C), ABC must be ccw
	return imag((c-b)*conj(p-c)*(a-p)*conj(b-a)) < 0;
}

struct QuadEdge {
	QuadEdge* rot = nullptr;
	QuadEdge* onext = nullptr;
	pt orig = INF_PT;
	bool used = false;
	QuadEdge* rev() const {return rot->rot;}
	QuadEdge* lnext() const {return rot->rev()->onext->rot;}
	QuadEdge* oprev() const {return rot->onext->rot;}
	pt dest() const {return rev()->orig;}
};

deque<QuadEdge> edgeData;

QuadEdge* makeEdge(pt from, pt to) {
	for (int _ : {0,1,2,3}) edgeData.push_back({});
	auto e = edgeData.end() - 4;
	for (int j : {0,1,2,3}) e[j].onext = e[j^3].rot = &e[j^(j>>1)];
	e[0].orig = from;
	e[1].orig = to;
	return &e[0];
}

void splice(QuadEdge* a, QuadEdge* b) {
	swap(a->onext->rot->onext, b->onext->rot->onext);
	swap(a->onext, b->onext);
}

QuadEdge* connect(QuadEdge* a, QuadEdge* b) {
	QuadEdge* e = makeEdge(a->dest(), b->orig);
	splice(e, a->lnext());
	splice(e->rev(), b);
	return e;
}

bool valid(QuadEdge* e, QuadEdge* base) {
	return cross(e->dest(), base->orig, base->dest()) < 0;
}

template<bool ccw>
QuadEdge* deleteAll(QuadEdge* e, QuadEdge* base) {
	if (valid(e, base)) {
		while (circ(base->dest(), base->orig, e->dest(), (ccw ? e->onext : e->oprev())->dest())) {
			QuadEdge* t = ccw ? e->onext : e->oprev();
			splice(e, e->oprev());
			splice(e->rev(), e->rev()->oprev());
			e = t;
	}}
	return e;
}

template<typename IT>
pair<QuadEdge*, QuadEdge*> rec(IT l, IT r) {
	int n = distance(l, r);
	if (n <= 3) {
		QuadEdge* a = makeEdge(l[0], l[1]);
		if (n == 2) return {a, a->rev()};
		QuadEdge* b = makeEdge(l[1], l[2]);
		splice(a->rev(), b);
		auto side = cross(l[0], l[1], l[2]);
		QuadEdge* c = nullptr;
		if (side != 0) c = connect(b, a);
		if (side >= 0) return {a, b->rev()};
		else return {c->rev(), c};
	}
	auto m = l + (n / 2);
	auto [ldo, ldi] = rec(l, m);
	auto [rdi, rdo] = rec(m, r);
	while (true) {
		if (cross(rdi->orig, ldi->orig, ldi->dest()) > 0) {
			ldi = ldi->lnext();
		} else if (cross(ldi->orig, rdi->orig, rdi->dest()) < 0) {
			rdi = rdi->rev()->onext;
		} else break;
	}
	QuadEdge* base = connect(rdi->rev(), ldi);
	if (ldi->orig == ldo->orig)	ldo = base->rev();
	if (rdi->orig == rdo->orig)	rdo = base;
	while (true) {
		QuadEdge* lcand = deleteAll<true>(base->rev()->onext, base);
		QuadEdge* rcand = deleteAll<false>(base->oprev(), base);
		if (!valid(lcand, base) && !valid(rcand, base))	break;
		if (!valid(lcand, base) || (valid(rcand, base) &&
		    circ(lcand->dest(), lcand->orig, rcand->orig, rcand->dest()))) {
			base = connect(rcand, base->rev());
		} else {
			base = connect(base->rev(), lcand->rev());
	}}
	return {ldo, rdo};
}

vector<pt> delaunay(vector<pt> pts) {
	if (sz(pts) <= 2) return {};
	sort(all(pts), [](const pt& a, const pt& b) {
		if (real(a) != real(b)) return real(a) < real(b);
		return imag(a) < imag(b);
	});
	QuadEdge* r = rec(all(pts)).first;
	vector<QuadEdge*> edges = {r};
	while (cross(r->onext->dest(), r->dest(), r->orig) < 0) r = r->onext;
	auto add = [&](QuadEdge* e){
		QuadEdge* cur = e;
		do {
			cur->used = true;
			pts.push_back(cur->orig);
			edges.push_back(cur->rev());
			cur = cur->lnext();
		} while (cur != e);
	};
	add(r);
	pts.clear();
	for (int i = 0; i < sz(edges); i++) {
		if (!edges[i]->used) add(edges[i]);
	}
	return pts;
}
