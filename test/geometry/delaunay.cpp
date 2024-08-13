#include "../util.h"
using pt = complex<lll>;
// Kreuzprodukt, 0, falls kollinear.
auto cross(pt a, pt b) {return imag(conj(a) * b);}
auto cross(pt p, pt a, pt b) {return cross(a - p, b - p);}
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <geometry/delaunay.cpp>

vector<pt> convexHull(vector<pt> pts){
	sort(all(pts), [](const pt& a, const pt& b){
		return real(a) == real(b) ? imag(a) < imag(b)
		                          : real(a) < real(b);
	});
	pts.erase(unique(all(pts)), pts.end());
	int k = 0;
	vector<pt> h(2 * sz(pts));
	auto half = [&](auto begin, auto end, int t) {
		for (auto it = begin; it != end; it++) {
			while (k > t && cross(h[k-2], h[k-1], *it) < 0) k--; //allow collinear points!
			h[k++] = *it;
	}};
	half(all(pts), 1); // Untere Hülle.
	half(next(pts.rbegin()), pts.rend(), k); // Obere Hülle.
	h.resize(k);
	return h;
}

lll area(const vector<pt>& poly) { //poly[0] == poly.back()
	lll res = 0;
	for (int i = 0; i + 1 < sz(poly); i++)
		res += cross(poly[i], poly[i + 1]);
	return res;
}

// Liegt p auf der Strecke a-b?
bool pointInLineSegment(pt a, pt b, pt p) {
	if (cross(a, b, p) != 0) return false;
	auto dist = norm(a - b);
	return norm(a - p) < dist && norm(b - p) < dist;
}

// Test auf Streckenschnitt zwischen a-b und c-d.
// (nur intern)
bool lineSegmentIntersection(pt a, pt b, pt c, pt d) {
	if (cross(a, b, c) == 0 && cross(a, b, d) == 0) {
		return pointInLineSegment(a,b,c) ||
		       pointInLineSegment(a,b,d) ||
		       pointInLineSegment(c,d,a) ||
		       pointInLineSegment(c,d,b);
	}
	return cross(a, b, c) * cross(a, b, d) < 0 &&
	       cross(c, d, a) * cross(c, d, b) < 0;
}

//  1 => c links von a->b
//  0 => a, b und c kolliniear
// -1 => c rechts von a->b
int ccw(pt a, pt b, pt c) {
	auto orien = cross(b - a, c - a);
	return (orien > 0) - (orien < 0);
}

bool inOutCirc(pt a, pt b, pt c, pt p) {
	lll p2 = norm(p);
	lll A = norm(a)-p2;
	lll B = norm(b)-p2;
	lll C = norm(c)-p2;
	return ccw(a, b, c) * (cross(p, a, b)*C + cross(p, b, c)*A + cross(p, c, a)*B) > 0;
}


void stress_test(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(3, 30);
		auto ps = Random::points<lll>(n, -range, range);
		bool skip = true;
		for (int i = 2; i < n; i++) skip &= cross(ps[i-2], ps[i-1], ps[i]) == 0;
		if (skip) continue;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				skip |= ps[i] == ps[j];
			}
		}
		if (skip) continue;

		auto hull = convexHull(ps);
		lll expectedArea = area(hull);
		hull.pop_back();

		auto got = delaunay(ps);
		if (sz(got) % 3 != 0) cerr << "error: not triangles" << FAIL;
		if (sz(got) / 3 + sz(hull) - 3 + 1 != 2 * sz(ps) - 4) cerr << "error: wrong number" << FAIL;

		//all triangles should be oriented ccw
		lll gotArea = 0;
		for (int i = 0; i < sz(got); i += 3) gotArea += cross(got[i], got[i+1], got[i+2]);
		if (gotArea != expectedArea) cerr << "error: wrong area" << FAIL;

		for (int i = 0; i < sz(got); i++) {
			int ii = i + 1;
			if (i / 3 != ii / 3) ii -= 3;
			for (int j = 0; j < i; j++) {
				int jj = j + 1;
				if (j / 3 != jj / 3) jj -= 3;

				if (got[i] == got[j] && got[ii] == got[jj]) cerr << "error: dublicate" << FAIL;
				if (lineSegmentIntersection(got[i], got[ii], got[j], got[jj])) cerr << "error: intersection" << FAIL;
			}
			bool seen = false;
			for (pt p : ps) seen |= p == got[i];
			if (!seen) cerr << "error: invalid point" << FAIL;
		}
		for (int i = 0; i < sz(got); i += 3) {
			for (pt p : ps) {
				if (p == got[i]) continue;
				if (p == got[i+1]) continue;
				if (p == got[i+2]) continue;
				if (inOutCirc(got[i], got[i+1], got[i+2], p)) cerr << "error: not delaunay" << FAIL;
			}
		}
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 100'000;
void performance_test() {
	timer t;
	auto ps = Random::points<lll>(N, -1'000'000'000, 1'000'000'000);
	t.start();
	auto got = delaunay(ps);
	t.stop();
	hash_t hash = sz(got);
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test(10);
	stress_test(10'000);
	stress_test(1'000'000'000);
	performance_test();
}
