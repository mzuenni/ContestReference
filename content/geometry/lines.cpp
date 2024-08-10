struct line {
	double a, b, c; // ax + by + c = 0; vertikale Gerade: b = 0
	line(pt p, pt q) : a(imag(p-q)), b(real(q-p)), c(cross({-b, a}, p)) {}
};

line pointsToLine(pt p1, pt p2) { // vertikale Gerade: b = 1 oder b = 0
	line l(0, 0);
	if (abs(real(p1 - p2)) < EPS) {
		l.a = 1; l.b = 0.0; l.c = -real(p1);
	} else {
		l.a = -imag(p1 - p2) / real(p1 - p2);
		l.b = 1.0;
		l.c = -(l.a * real(p1)) - imag(p1);
	}
	return l;
}

bool parallel(line l1, line l2) { // braucht b in {0, 1}
	return (abs(l1.a - l2.a) < EPS) && (abs(l1.b - l2.b) < EPS);
}

bool same(line l1, line l2) { // braucht b in {0, 1}
	return parallel(l1, l2) && (abs(l1.c - l2.c) < EPS);
}

bool intersect(line l1, line l2, pt& res) { // braucht b in {0, 1}
	if (parallel(l1, l2)) return false;
	double y, x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
	if (abs(l1.b) > EPS) y = -(l1.a * x + l1.c);
	else y = -(l2.a * x + l2.c);
	res = {x, y};
	return true;
}
