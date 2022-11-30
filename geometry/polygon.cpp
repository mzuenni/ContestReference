// Berechnet den Flächeninhalt eines Polygons
// (nicht selbstschneidend).
// Punkte gegen den Uhrzeigersinn: positiv, sonst negativ.
double area(const vector<pt>& polygon) {//points unique
	double res = 0; int n = sz(polygon);
	for (int i = 0; i < n; i++)
		res += cross(polygon[i], polygon[(i + 1) % n]);
	return 0.5 * res;
}

// Testet, ob ein Punkt im Polygon liegt (beliebige Polygone).
bool inside(pt p, const vector<pt>& polygon) {//points unique
	pt rayEnd = p + pt(1, 1000000);
	int counter = 0, n = sz(polygon);
	for (int i = 0; i < n; i++) {
		pt start = polygon[i], end = polygon[(i + 1) % n];
		if (lineSegmentIntersection(p, rayEnd, start, end)) {
			counter++;
	}}
	return counter & 1;
}

//convex hull without duplicates, h[0] == h.back()
bool inside(pt p, const vector<pt>& hull) {
	if (orientation(hull[0], hull.back(), p) > 0) return false;
	ll l = 0, r = sz(hull) - 1;
	while (l + 1 < r) {
		ll m = (l + r) / 2;
		if (orientation(hull[0], hull[m], p) >= 0) l = m;
		else r = m;
	}
	return orientation(hull[l], hull[r], p) >= 0;
}

void rotateMin(vector<pt>& hull) {
	auto mi = min_element(all(hull), [](const pt& a, const pt& b){
		return real(a) == real(b) ? imag(a) < imag(b)
															: real(a) < real(b);
	});
	rotate(hull.begin(), mi, hull.end());
}

//convex hulls without duplicates, h[0] != h.back()
vector<pt> minkowski(vector<pt> ps, vector<pt> qs) {
	rotateMin(ps);
	rotateMin(qs);
	ps.push_back(ps[0]);
	qs.push_back(qs[0]);
	ps.push_back(ps[1]);
	qs.push_back(qs[1]);
	vector<pt> res;
	for (ll i = 0, j = 0; i + 2 < sz(ps) || j + 2 < sz(qs);) {
		res.push_back(ps[i] + qs[j]);
		auto c = cross(ps[i + 1] - ps[i], qs[j + 1] - qs[j]);
		if(c <= 0) i++;
		if(c >= 0) j++;
	}
	return res;
}

//convex hulls without duplicates, h[0] != h.back()
double dist(const vector<pt>& ps, const vector<pt>& qs) {
	for (pt& q : qs) q *= -1;
	auto p = minkowski(ps, qs);
	p.push_back(p[0]);
	double res = 0.0;
	//bool intersect = true;
	for (ll i = 0; i + 1 < sz(p); i++) {
		//intersect &= cross(p[i], p[i+1] - p[i]) <= 0;
		res = max(res, cross(p[i], p[i+1]-p[i]) / abs(p[i+1]-p[i]));
	}
	return res;
}
