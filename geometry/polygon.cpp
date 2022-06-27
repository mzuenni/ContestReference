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
