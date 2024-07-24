// Skalarprodukt
auto operator|(pt3 a, pt3 b) {
	return a.x * b.x + a.y*b.y + a.z*b.z;
}
auto dot(pt3 a, pt3 b) {return a|b;}

// Kreuzprodukt
pt3 operator*(pt3 a, pt3 b) {return {a.y*b.z - a.z*b.y,
                                     a.z*b.x - a.x*b.z,
                                     a.x*b.y - a.y*b.x};}
pt3 cross(pt3 a, pt3 b) {return a*b;}

// Länge von a
double abs(pt3 a) {return sqrt(dot(a, a));}
double abs(pt3 a, pt3 b) {return abs(b - a);}

// Mixedprodukt
auto mixed(pt3 a, pt3 b, pt3 c) {return a*b|c;};

// orientierung von p zu der Ebene durch a, b, c
// -1 => gegen den Uhrzeigersinn,
//  0 => kolliniear,
//  1 => im Uhrzeigersinn.
int ccw(pt3 a, pt3 b, pt3 c, pt3 p) {
	auto orien = mixed(b - a, c - a, p - a);
	return (orien > EPS) - (orien < -EPS);
}

// Entfernung von Punkt p zur Ebene a,b,c.
double distToPlane(pt3 a, pt3 b, pt3 c, pt3 p) {
	pt3 n = cross(b-a, c-a);
	return (abs(dot(n, p)) - dot(n, a)) / abs(n);
}

// Liegt p in der Ebene a,b,c?
bool pointOnPlane(pt3 a, pt3 b, pt3 c, pt3 p) {
	return ccw(a, b, c, p) == 0;
}

// Schnittpunkt von der Grade a-b und der Ebene c,d,e
// die Grade darf nicht parallel zu der Ebene sein!
pt3 linePlaneIntersection(pt3 a, pt3 b, pt3 c, pt3 d, pt3 e) {
	pt3 n = cross(d-c, e-c);
	pt3 d = b - a;
	return a - d * (dot(n, a) - dot(n, c)) / dot(n, d);
}

// Abstand zwischen der Grade a-b und c-d
double lineLineDist(pt3 a, pt3 b, pt3 c, pt3 d) {
	pt3 n = cross(b - a, d - c);
	if (abs(n) < EPS) return distToLine(a, b, c);
	return abs(dot(a - c, n)) / abs(n);
}
