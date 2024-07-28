// Liegt p auf der Geraden a-b? 2d und 3d
bool pointOnLine(pt a, pt b, pt p) {
	return ccw(a, b, p) == 0;
}

// Test auf Linienschnitt zwischen a-b und c-d. (nicht identisch)
bool lineIntersection(pt a, pt b, pt c, pt d) {
	return abs(cross(a - b, c - d)) < EPS;
}

// Berechnet den Schnittpunkt der Graden a-b und c-d.
// die Graden dürfen nicht parallel sein!
pt lineIntersection2(pt a, pt b, pt c, pt d) {
	double x = cross(b - a, d - c);
	double y = cross(c - a, d - c);
	return a + y/x*(b - a);
}

// Entfernung von Punkt p zur Geraden durch a-b. 2d und 3d
double distToLine(pt a, pt b, pt p) {
	return abs(cross(p - a, b - a)) / abs(b - a);
}

// Projiziert p auf die Gerade a-b
pt projectToLine(pt a, pt b, pt p) {
	return a + (b - a) * dot(p - a, b - a) / norm(b - a);
}

// sortiert alle Punkte pts auf einer Linie entsprechend dir
void sortLine(pt dir, vector<pt>& pts) { // (2d und 3d)
	sort(all(pts), [&](pt a, pt b){
		return dot(dir, a) < dot(dir, b);
	});
}

// Liegt p auf der Strecke a-b? (nutze < für inberhalb)
bool pointOnSegment(pt a, pt b, pt p) {
	if (ccw(a, b, p) != 0) return false;
	auto dist = norm(a - b);
	return norm(a - p) <= dist && norm(b - p) <= dist;
}

// Entfernung von Punkt p zur Strecke a-b.
double distToSegment(pt a, pt b, pt p) {
	if (a == b) return abs(p - a);
	if (dot(p - a, b - a) <= 0) return abs(p - a);
	if (dot(p - b, b - a) >= 0) return abs(p - b);
	return distToLine(a, b, p);
}

// Test auf Streckenschnitt zwischen a-b und c-d.
bool segmentIntersection(pt a, pt b, pt c, pt d) {
	if (ccw(a, b, c) == 0 && ccw(a, b, d) == 0)
		return pointOnSegment(a,b,c) ||
		       pointOnSegment(a,b,d) ||
		       pointOnSegment(c,d,a) ||
		       pointOnSegment(c,d,b);
	return ccw(a, b, c) * ccw(a, b, d) <= 0 &&
	       ccw(c, d, a) * ccw(c, d, b) <= 0;
}

// Berechnet die Schnittpunkte der Strecken a-b und c-d.
// Enthält entweder keinen Punkt, den einzigen Schnittpunkt
// oder die Endpunkte der Schnittstrecke.
vector<pt> segmentIntersection2(pt a, pt b, pt c, pt d) {
	double x = cross(b - a, d - c);
	double y = cross(c - a, d - c);
	double z = cross(b - a, a - c);
	if (x < 0) {x = -x; y = -y; z = -z;}
	if (y < -EPS || y-x > EPS || z < -EPS || z-x > EPS) return {};
	if (x > EPS) return {a + y/x*(b - a)};
	vector<pt> result;
	auto insertUnique = [&](pt p) {
		for (auto q : result) if (abs(p - q) < EPS) return;
		result.push_back(p);
	};
	if (dot(c-a, d-a) < EPS) insertUnique(a);
	if (dot(c-b, d-b) < EPS) insertUnique(b);
	if (dot(a-c, b-c) < EPS) insertUnique(c);
	if (dot(a-d, b-d) < EPS) insertUnique(d);
	return result;
}

// Kürzeste Entfernung zwischen den Strecken a-b und c-d.
double distBetweenSegments(pt a, pt b, pt c, pt d) {
	if (segmentIntersection(a, b, c, d)) return 0.0;
	return min({distToSegment(a, b, c), distToSegment(a, b, d),
	            distToSegment(c, d, a), distToSegment(c, d, b)});
}
