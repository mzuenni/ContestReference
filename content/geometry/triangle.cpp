// Mittelpunkt des Dreiecks abc.
pt centroid(pt a, pt b, pt c) {return (a + b + c) / 3.0;}

// Flächeninhalt eines Dreicks bei bekannten Eckpunkten.
double area(pt a, pt b, pt c) {
	return abs(cross(a, b, c)) / 2.0;
}

// Flächeninhalt eines Dreiecks bei bekannten Seitenlängen.
double area(double a, double b, double c) {
	double s = (a + b + c) / 2.0; //unpräzise
	return sqrt(s * (s-a) * (s-b) * (s-c));
}

// Zentrum des größten Kreises im Dreiecke
pt inCenter(pt a, pt b, pt c) {
	double x = abs(a-b), y = abs(b-c), z = abs(a-c);
	return (y*a + z*b + x*c) / (x+y+z);
}

// Zentrum des Kreises durch alle Eckpunkte
// a, b und c nicht kollinear
pt circumCenter(pt a, pt b, pt c) {
	b -= a, c -= a;
	pt d = b * norm(c) - c * norm(b);
	d = {-d.imag(), d.real()};
	return a + d / cross(b, c) / 2.0;
}

// -1 => p außerhalb Kreis durch a,b,c
//  0 => p auf Kreis durch a,b,c
//  1 => p im Kreis durch a,b,c
int insideOutCenter(pt a, pt b, pt c, pt p) {// braucht lll
	return ccw(a,b,c) * sgn(imag((c-b)*conj(p-c)*(a-p)*conj(b-a)));
}

// Sind die Dreiecke a1, b1, c1, and a2, b2, c2 ähnlich?
// Erste Zeile testet Ähnlichkeit mit gleicher Orientierung,
// zweite Zeile testet Ähnlichkeit mit verschiedener Orientierung
bool similar(pt a1, pt b1, pt c1, pt a2, pt b2, pt c2) {
	return (b2-a2) * (c1-a1) == (b1-a1) * (c2-a2) ||
	       (b2-a2) * conj(c1-a1) == conj(b1-a1) * (c2-a2);
}
