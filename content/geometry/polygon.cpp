// Flächeninhalt eines Polygons (nicht selbstschneidend).
// Punkte gegen den Uhrzeigersinn: positiv, sonst negativ.
double area(const vector<pt>& poly) { //poly[0] == poly.back()
	ll res = 0;
	for (int i = 0; i + 1 < sz(poly); i++)
		res += cross(poly[i], poly[i + 1]);
	return 0.5 * res;
}

// Anzahl ccw drehungen einer Polyline um einen Punkt
// p nicht auf rand und poly[0] == poly.back()
// res != 0 or (res & 1) != 0 um inside zu prüfen bei
// selbstschneidenden Polygonen (definitions Sache)
ll windingNumber(pt p, const vector<pt>& poly) {
	ll res = 0;
	for (int i = 0; i + 1 < sz(poly); i++) {
		pt a = poly[i], b = poly[i + 1];
		if (real(a) > real(b)) swap(a, b);
		if (real(a) <= real(p) && real(p) < real(b) &&
		    cross(p, a, b) < 0) {
			res += ccw(p, poly[i], poly[i + 1]);
	}}
	return res;
}

// Testet, ob ein Punkt im Polygon liegt (beliebige Polygone).
// Ändere Zeile 32 falls rand zählt, poly[0] == poly.back()
bool inside(pt p, const vector<pt>& poly) {
	bool in = false;
	for (int i = 0; i + 1 < sz(poly); i++) {
		pt a = poly[i], b = poly[i + 1];
		if (pointOnSegment(a, b, p)) return false;
		if (real(a) > real(b)) swap(a,b);
		if (real(a) <= real(p) && real(p) < real(b) &&
		    cross(p, a, b) < 0) {
			in ^= 1;
	}}
	return in;
}

// convex hull without duplicates, h[0] != h.back()
// apply comments if border counts as inside
bool insideConvex(pt p, const vector<pt>& hull) {
	int l = 0, r = sz(hull) - 1;
	if (cross(hull[0], hull[r], p) >= 0) return false; // > 0
	while (l + 1 < r) {
		int m = (l + r) / 2;
		if (cross(hull[0], hull[m], p) > 0) l = m; // >= 0
		else r = m;
	}
	return cross(hull[l], hull[r], p) > 0; // >= 0
}

void rotateMin(vector<pt>& hull) {
	auto mi = min_element(all(hull), [](const pt& a, const pt& b){
		return real(a) == real(b) ? imag(a) < imag(b)
		                          : real(a) < real(b);
	});
	rotate(hull.begin(), mi, hull.end());
}

// convex hulls without duplicates, h[0] != h.back()
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
		if(c >= 0) i++;
		if(c <= 0) j++;
	}
	return res;
}

// convex hulls without duplicates, h[0] != h.back()
double dist(const vector<pt>& ps, vector<pt> qs) {
	for (pt& q : qs) q *= -1;
	auto p = minkowski(ps, qs);
	p.push_back(p[0]);
	double res = INF;
	bool intersect = true;
	for (ll i = 0; i + 1 < sz(p); i++) {
		intersect &= cross(p[i], p[i+1]) >= 0;
		res = min(res, distToSegment(p[i], p[i+1], 0));
	}
	return intersect ? 0 : res;
}

bool left(pt of, pt p) {return cross(p, of) < 0 ||
                       (cross(p, of) == 0 && dot(p, of) > 0);}

// convex hulls without duplicates, hull[0] == hull.back() and
// hull[0] must be a convex point (with angle < pi)
// returns index of corner where dot(dir, corner) is maximized
int extremal(const vector<pt>& hull, pt dir) {
	dir *= pt(0, 1);
	int l = 0, r = sz(hull) - 1;
	while (l + 1 < r) {
		int m = (l + r) / 2;
		pt dm = hull[m+1]-hull[m];
		pt dl = hull[l+1]-hull[l];
		if (left(dl, dir) != left(dl, dm)) {
			if (left(dl, dm)) l = m;
			else r = m;
		} else {
			if (cross(dir, dm) < 0) l = m;
			else r = m;
	}}
	return r % (sz(hull) - 1);
}

// convex hulls without duplicates, hull[0] == hull.back() and
// hull[0] must be a convex point (with angle < pi)
// {} if no intersection
// {x} if corner is only intersection
// {i, j} segments (i,i+1) and (j,j+1) intersected (if only the
// border is intersected corners i and j are the start and end)
vector<int> intersectLine(const vector<pt>& hull, pt a, pt b) {
	int endA = extremal(hull, (a-b) * pt(0, 1));
	int endB = extremal(hull, (b-a) * pt(0, 1));
	// cross == 0 => line only intersects border
	if (cross(hull[endA], a, b) > 0 ||
	    cross(hull[endB], a, b) < 0) return {};

	int n = sz(hull) - 1;
	vector<int> res;
	for (auto _ : {0, 1}) {
		int l = endA, r = endB;
		if (r < l) r += n;
		while (l + 1 < r) {
			int m = (l + r) / 2;
			if (cross(hull[m % n], a, b) <= 0 &&
			    cross(hull[m % n], a, b) != cross(hull[endB], a, b))
				l = m;
			else r = m;
		}
		if (cross(hull[r % n], a, b) == 0) l++;
		res.push_back(l % n);
		swap(endA, endB);
		swap(a, b);
	}
	if (res[0] == res[1]) res.pop_back();
	return res;
}

