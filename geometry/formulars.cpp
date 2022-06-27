// Komplexe Zahlen als Darstellung für Punkte. 
// Wenn immer möglich complex<int> verwenden.
// Funktionen wie abs() geben dann int zurück.
using pt = complex<double>;

// PIL < PI < PIU
constexpr double PIU = acos(-1.0l);
constexpr double PIL = PIU-2e-19l;

// Winkel zwischen Punkt und x-Achse in [-PI, PI].
double angle(pt a) {return arg(a);}

// rotiert Punkt im Uhrzeigersinn um den Ursprung.
pt rotate(pt a, double theta) {return a * exp(pt(0.0, theta));}

// Skalarprodukt.
double dot(pt a, pt b) {return real(conj(a) * b);}

// abs()^2.(pre c++20)
double norm(pt a) {return dot(a, a);}

// Kreuzprodukt, 0, falls kollinear.
double cross(pt a, pt b) {return imag(conj(a) * b);}
double cross(pt p, pt a, pt b) {return cross(a - p, b - p);}

// -1 => gegen den Uhrzeigersinn
//  0 => kolliniear
//  1 => im Uhrzeigersinn.
int orientation(pt a, pt b, pt c) {
	double orien = cross(b - a, c - a);
	return (orien > EPS) - (orien < -EPS);
}

// Liegt d in der gleichen Ebene wie a, b, und c?
bool isCoplanar(pt a, pt b, pt c, pt d) {
	return abs((b - a) * (c - a) * (d - a)) < EPS;
}
