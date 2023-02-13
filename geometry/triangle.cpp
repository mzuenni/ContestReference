// Mittelpunkt des Dreiecks abc.
pt centroid(pt a, pt b, pt c) {return (a + b + c) / 3.0;}

// Flächeninhalt eines Dreicks bei bekannten Eckpunkten.
double area(pt a, pt b, pt c) {
	return abs(cross(b - a, c - a)) / 2.0;
}

// Flächeninhalt eines Dreiecks bei bekannten Seitenlängen.
double area(double a, double b, double c) {
	double s = (a + b + c) / 2.0;
	return sqrt(s * (s-a) * (s-b) * (s-c));
}

// Zentrum des größten Kreises im Dreiecke
pt inCenter(pt a, pt b, pt c) {
	double x = abs(a-b), y = abs(b-c), z = abs(a-c);
	return (y*a + z*b + x*c) / (x+y+z);
}

// Zentrum des Kreises durch alle Eckpunkte
pt outCenter(pt a, pt b, pt c) {
	double d = 2.0 * (real(a) * imag(b-c) +
	                  real(b) * imag(c-a) +
	                  real(c) * imag(a-b));
	return (a*conj(a)*conj(b-c) +
	        b*conj(b)*conj(c-a) +
	        c*conj(c)*conj(a-b)) / d;
}

// Sind die Dreiecke a1, b1, c1, and a2, b2, c2 ähnlich?
// Erste Zeile testet Ähnlichkeit mit gleicher Orientierung,
// zweite Zeile testet Ähnlichkeit mit verschiedener Orientierung
bool similar (pt a1, pt b1, pt c1, pt a2, pt b2, pt c2) {
	return ((b2-a2) * (c1-a1) == (b1-a1) * (c2-a2) ||
	        (b2-a2) * (conj(c1)-conj(a1)) == (conj(b1)-conj(a1))
			* (c2-a2)
	);
}
