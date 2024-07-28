#include <geometry/sortAround.cpp>

namespace details {
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
		return ccw(a, b, c) * ccw(a, b, d) < 0 &&
		       ccw(c, d, a) * ccw(c, d, b) < 0;
	}
}

namespace Random {
	vector<ll> partition(ll n, std::size_t k){//min = 0;
		n += k;
		vector<ll> res = Random::distinct<ll>(k-1, 1, n);
		sort(all(res));
		res.emplace_back(n);
		ll last = 0;
		for (std::size_t i = 0; i < k; i++) {
			res[i] -= last;
			last += res[i];
			res[i]--;
		}
		return res;
	}

	vector<pt> convex(int n, ll dim) {
		binomial_distribution<int> binomial(n - 2, 0.5);

		while (true) {
			int left = 1 + binomial(Random::rng);
			int down = 1 + binomial(Random::rng);
			auto x = Random::partition(2 * dim - 2, left);
			auto y = Random::partition(2 * dim - 2, down);
			for (auto& z : x) z = -z;
			for (auto& z : y) z = -z;
			for (auto z : Random::partition(2 * dim - 2, n - left)) x.push_back(z);
			for (auto z : Random::partition(2 * dim - 2, n - down)) y.push_back(z);
			auto itX = std::partition(x.begin(), x.end(), [](ll z){return z == 0;});
			auto itY = std::partition(y.begin(), y.end(), [](ll z){return z != 0;});
			if (distance(x.begin(), itX) + distance(itY, y.end()) > n) continue;
			shuffle(itX, x.end(), Random::rng);
			if (itX != x.begin()) shuffle(y.begin(), itY, Random::rng);

			vector<pt> dirs(n);
			for (size_t i = 0; i < dirs.size(); i++) {
				dirs[i] = pt(x[i], y[i]);
			}
			sortAround(0, dirs);

			vector<pt> res = {{0, 0}};
			ll maxX = 0;
			ll maxY = 0;
			for (auto dir : dirs) {
				pt tmp(real(res.back()) + real(dir),
				       imag(res.back()) + imag(dir));
				maxX = std::max<ll>(maxX, real(tmp));
				maxY = std::max<ll>(maxY, imag(tmp));
				res.emplace_back(tmp);
			}
			res.pop_back();
			for (auto& point : res) {
				point = pt(real(point) + dim - 1 - maxX,
				           imag(point) + dim - 1 - maxY);
			}
			bool strict = true;
			for (int i = 0; i < n; i++) strict &= cross(res[i], res[(i + 1) % n], res[(i + 2) % n]) != 0;
			if (strict) return res;
		}
	}

	vector<pt> polygon(int n, ll dim) {
		while (true) {
			vector<pt> ps = points<pt::value_type>(n, -dim, dim);
			bool coolinear = false;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < i; j++) {
					for (int k = 0; k < j; k++) {
						coolinear |= cross(ps[i], ps[j], ps[k]) == 0;
					}
				}
			}
			if (coolinear) continue;

			bool changed;
			do {
				changed = false;
				for (int i = 0; i < n && !changed; i++) {
					for (int j = i + 1; j < n && !changed; j++) {
						if (details::lineSegmentIntersection(ps[i], ps[(i+1) % n], ps[j], ps[(j+1) % n])) {
							reverse(ps.begin() + i + 1, ps.begin() + j + 1);
							changed = true;
						}
					}
				}
			} while (changed);
			return ps;
		}
	}

	pt integerPoint(ll range) {
		return pt(integer<ll>(-range, range),
		          integer<ll>(-range, range));
	}

	vector<pt> integerPoints(std::size_t n, ll range) {
		vector<pt> res(n);
		for (auto& p : res) p = integerPoint(range);
		return res;
	}

	array<pt, 2> line(ll range) {
		pt a = integerPoint(range);
		pt b = a;
		while (b == a) b = integerPoint(range);
		return {a, b};
	}

	array<pt, 3> triangle(ll range) {
		pt a = integerPoint(range);
		pt b = a;
		while (b == a) b = integerPoint(range);
		pt c = a;
		while (ccw(a, b, c) == 0) c = integerPoint(range);
		return {a, b, c};
	}
}