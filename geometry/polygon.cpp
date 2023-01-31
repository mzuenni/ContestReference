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

bool left(pt of, pt p) {return cross(p, of) < 0 || 
                       (cross(p, of) == 0 && dot(p, of) > 0);}

// convex hulls without duplicates, poly[0] == poly.back() and
// poly[0] must be a convex point (with angle < pi)
// returns index of corner where dot(dir, corner) is maximized
int extremal(const vector<pt>& poly, pt dir) {
	dir *= pt(0, 1);
	int l = 0;
	int r = sz(poly) - 1;
	while (l + 1 < r) {
		int m = (l + r) / 2;
		pt dm = poly[m+1]-poly[m];
		pt dl = poly[l+1]-poly[l];
		if (left(dl, dir) != left(dl, dm)) {
			if (left(dl, dm)) l = m;
			else r = m;
		} else {
			if (cross(dir, dm) < 0) l = m;
			else r = m;
	}}
	return r;
}

// convex hulls without duplicates, poly[0] == poly.back() and
// poly[0] must be a convex point (with angle < pi)
// {} if no intersection
// {x} if corner is only intersection
// {a, b} segments (a,a+1) and (b,b+1) intersected (if only the
// border is intersected corners a and b are the start and end)
vector<int> intersect(const vector<pt>& poly, pt a, pt b) {
	int endA = extremal(poly, (a-b) * pt(0, 1));
	int endB = extremal(poly, (b-a) * pt(0, 1));

	// cross == 0 => line only intersects border
	if (cross(poly[endA], a, b) > 0 ||
	    cross(poly[endB], a, b) < 0) return {};

	int n = sz(poly) - 1;
	vector<int> res;
	for (auto _ : {0, 1}) {
		int l = endA;
		int r = endB;
		if (r < l) r += n;
		while (l+1 < r) {
			int m = (l + r) / 2;
			if (cross(poly[m % n], a, b) <= 0 &&
			    cross(poly[m % n], a, b) != cross(poly[endB], a, b)) {
				l = m;
			} else {
				r = m;
		}}
		if (cross(poly[r % n], a, b) == 0) l++;
		res.push_back(l % n);
		swap(endA, endB);
		swap(a, b);
	}
	if (res[0] == res[1]) res.pop_back();
	return res;
}

