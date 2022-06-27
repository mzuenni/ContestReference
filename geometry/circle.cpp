// berechnet die Schnittpunkte von zwei kreisen
// (Kreise dürfen nicht gleich sein!)
vector<pt> circleIntersection(pt c1, double r1, 
															pt c2, double r2) {
	double d = abs(c1 - c2);
	if (d < abs(r1 - r2) || d > abs(r1 + r2)) return {};
	double a = (r1 * r1 - r2 * r2 + d * d) / (2 * d);
	pt p = (c2 - c1) * a / d + c1;
	if (d == abs(r1 - r2) || d == abs(r1 + r2)) return {p};
	double h = sqrt(r1 * r1 - a * a);
	return {p + pt{0, 1} * (c2 - c1) * h / d,
					p - pt{0, 1} * (c2 - c1) * h / d};
}

// berechnet die Schnittpunkte zwischen
// einem Kreis(Kugel) und einer Grade 2d und 3d
vector<pt> circleRayIntersection(pt center, double r, 
																 pt orig, pt dir) {
	vector<pt> result;
	double a = dot(dir, dir);
	double b = 2 * dot(dir, orig - center);
	double c = dot(orig - center, orig - center) - r * r;
	double discr = b * b - 4 * a * c;
	if (discr >= 0) {
		//t in [0, 1] => schnitt mit segment [orig, orig + dir]
		double t1 = -(b + sqrt(discr)) / (2 * a);
		double t2 = -(b - sqrt(discr)) / (2 * a);
		if (t1 >= 0) result.push_back(t1 * dir + orig);
		if (t2 >= 0 && abs(t1 - t2) > EPS) {
			result.push_back(t2 * dir + orig);
	}}
	return result;
}
