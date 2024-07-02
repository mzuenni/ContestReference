// Test auf Streckenschnitt zwischen a-b und c-d.
bool lineSegmentIntersection(pt a, pt b, pt c, pt d) {
	if (orientation(a, b, c) == 0 && orientation(a, b, d) == 0)
			return pointOnLineSegment(a,b,c) ||
			       pointOnLineSegment(a,b,d) ||
			       pointOnLineSegment(c,d,a) ||
			       pointOnLineSegment(c,d,b);
	return orientation(a, b, c) * orientation(a, b, d) <= 0 &&
	       orientation(c, d, a) * orientation(c, d, b) <= 0;
}

// Berechnet die Schnittpunkte der Strecken p0-p1 und p2-p3.
// Enthält entweder keinen Punkt, den einzigen Schnittpunkt
// oder die Endpunkte der Schnittstrecke.
vector<pt> lineSegmentIntersection(pt p0, pt p1, pt p2, pt p3) {
	double a = cross(p1 - p0, p3 - p2);
	double b = cross(p2 - p0, p3 - p2);
	double c = cross(p1 - p0, p0 - p2);
	if (a < 0) {a = -a; b = -b; c = -c;}
	if (b < -EPS || b-a > EPS || c < -EPS || c-a > EPS) return {};
	if (a > EPS) return {p0 + b/a*(p1 - p0)};
	vector<pt> result;
	auto insertUnique = [&](pt p) {
		for (auto q: result) if (abs(p - q) < EPS) return;
		result.push_back(p);
	};
	if (dot(p2-p0, p3-p0) < EPS) insertUnique(p0);
	if (dot(p2-p1, p3-p1) < EPS) insertUnique(p1);
	if (dot(p0-p2, p1-p2) < EPS) insertUnique(p2);
	if (dot(p0-p3, p1-p3) < EPS) insertUnique(p3);
	return result;
}

// Entfernung von Punkt p zur Geraden durch a-b. 2d und 3d
double distToLine(pt a, pt b, pt p) {
	return abs(cross(p - a, b - a)) / abs(b - a);
}

// Projiziert p auf die Gerade a-b
pt projectToLine(pt a, pt b, pt p) {
	return a + (b - a) * dot(p - a, b - a) / norm(b - a);
}

// Liegt p auf der Geraden a-b? 2d und 3d
bool pointOnLine(pt a, pt b, pt p) {
	return cross(a, b, p) == 0;
}

// Test auf Linienschnitt zwischen a-b und c-d.
bool lineIntersection(pt a, pt b, pt c, pt d) {
	return abs(cross(a - b, c - d)) < EPS;
}

// Berechnet den Schnittpunkt der Graden p0-p1 und p2-p3.
// die Graden dürfen nicht parallel sein!
pt lineIntersection(pt p0, pt p1, pt p2, pt p3) {
	double a = cross(p1 - p0, p3 - p2);
	double b = cross(p2 - p0, p3 - p2);
	return {p0 + b/a*(p1 - p0)};
}

// Liegt p auf der Strecke a-b?
bool pointOnLineSegment(pt a, pt b, pt p) {
	if (cross(a, b, p) != 0) return false;
	double dist = norm(a - b);
	return norm(a - p) <= dist && norm(b - p) <= dist;
}

// Entfernung von Punkt p zur Strecke a-b.
double distToSegment(pt a, pt b, pt p) {
	if (a == b) return abs(p - a);
	if (dot(p - a, b - a) <= 0) return abs(p - a);
	if (dot(p - b, b - a) >= 0) return abs(p - b);
	return distToLine(a, b, p);
}

// Kürzeste Entfernung zwischen den Strecken a-b und c-d.
double distBetweenSegments(pt a, pt b, pt c, pt d) {
	if (lineSegmentIntersection(a, b, c, d)) return 0.0;
	return min({distToSegment(a, b, c), distToSegment(a, b, d),
	            distToSegment(c, d, a), distToSegment(c, d, b)});
}

// sortiert alle Punkte pts auf einer Linie entsprechend dir
void sortLine(pt dir, vector<pt>& pts) { // (2d und 3d)
	sort(all(pts), [&](pt a, pt b){
		return dot(dir, a) < dot(dir, b);
	});
}
