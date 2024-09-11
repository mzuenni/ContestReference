#include "../util.h"
constexpr ll EPS = 0;
#define double ll
#define polar polar<ll>
#include <geometry/formulas.cpp>
#undef polar
#undef double
#include "../geometry.h"
ll sgn(ll x) {
	return (x > 0) - (x < 0);
}
#include <geometry/hpi.cpp>

//https://cp-algorithms.com/geometry/halfplane-intersection.html
namespace cpalgo {
	// Redefine epsilon and infinity as necessary. Be mindful of precision errors.
	const long double eps = 1e-9, inf = 1e9; 

	// Basic point/vector struct.
	struct Point { 

		long double x, y;
		explicit Point(long double x_ = 0, long double y_ = 0) : x(x_), y(y_) {}
		Point(pt p) : x(real(p)), y(imag(p)) {}

		// Addition, substraction, multiply by constant, dot product, cross product.

		friend Point operator + (const Point& p, const Point& q) {
			return Point(p.x + q.x, p.y + q.y); 
		}

		friend Point operator - (const Point& p, const Point& q) { 
			return Point(p.x - q.x, p.y - q.y); 
		}

		friend Point operator * (const Point& p, const long double& k) { 
			return Point(p.x * k, p.y * k); 
		} 

		friend long double dot(const Point& p, const Point& q) {
			return p.x * q.x + p.y * q.y;
		}

		friend long double cross(const Point& p, const Point& q) { 
			return p.x * q.y - p.y * q.x; 
		}

		friend std::ostream& operator<<(std::ostream& os, const Point& p) {
			return os << "(" << p.x << ", " << p.y << ")";
		}


	};

	// Basic half-plane struct.
	struct Halfplane { 

		// 'p' is a passing point of the line and 'pq' is the direction vector of the line.
		Point p, pq; 
		long double angle;

		Halfplane() {}
		Halfplane(const Point& a, const Point& b) : p(a), pq(b - a) {
			angle = atan2l(pq.x, -pq.y);//patched to get same sort
		}
		Halfplane(array<pt, 2> ps) : Halfplane(ps[0], ps[1]) {}
		Halfplane(hp h) : Halfplane(h.from, h.to) {}

		// Check if point 'r' is outside this half-plane. 
		// Every half-plane allows the region to the LEFT of its line.
		bool out(const Point& r) {
			return cross(pq, r - p) < -eps; 
		}

		// Comparator for sorting. 
		bool operator < (const Halfplane& e) const { 
			return angle < e.angle;
		} 

		// Intersection point of the lines of two half-planes. It is assumed they're never parallel.
		friend Point inter(const Halfplane& s, const Halfplane& t) {
			long double alpha = cross((t.p - s.p), t.pq) / cross(s.pq, t.pq);
			return s.p + (s.pq * alpha);
		}

		friend std::ostream& operator<<(std::ostream& os, const Halfplane& hp) {
			return os << hp.p << " " << hp.p+hp.pq;
		}
	};

	// Actual algorithm
	vector<Point> hp_intersect(vector<Halfplane>& H) { 

		/*Point box[4] = {  // Bounding box in CCW order
			Point(inf, inf), 
			Point(-inf, inf), 
			Point(-inf, -inf), 
			Point(inf, -inf) 
		};

		for(int i = 0; i<4; i++) { // Add bounding box half-planes.
			Halfplane aux(box[i], box[(i+1) % 4]);
			H.push_back(aux);
		}*/
		// Add bounding box half-planes, fixed:
		H.push_back({pt( 1e9,  1e9), pt( 1e9-1,  1e9  )});
		H.push_back({pt(-1e9,  1e9), pt(-1e9  ,  1e9-1)});
		H.push_back({pt(-1e9, -1e9), pt(-1e9+1, -1e9  )});
		H.push_back({pt( 1e9, -1e9), pt( 1e9  , -1e9+1)});

		// Sort by angle and start algorithm
		sort(H.begin(), H.end());
		deque<Halfplane> dq;
		int len = 0;
		for(int i = 0; i < int(H.size()); i++) {

			// Remove from the back of the deque while last half-plane is redundant
			while (len > 1 && H[i].out(inter(dq[len-1], dq[len-2]))) {
				dq.pop_back();
				--len;
			}

			// Remove from the front of the deque while first half-plane is redundant
			while (len > 1 && H[i].out(inter(dq[0], dq[1]))) {
				dq.pop_front();
				--len;
			}

			// Special case check: Parallel half-planes
			if (len > 0 && fabsl(cross(H[i].pq, dq[len-1].pq)) < eps) {
				// Opposite parallel half-planes that ended up checked against each other.
				if (dot(H[i].pq, dq[len-1].pq) < 0.0)
					return vector<Point>();

				// Same direction half-plane: keep only the leftmost half-plane.
				if (H[i].out(dq[len-1].p)) {
					dq.pop_back();
					--len;
				}
				else continue;
			}

			// Add new half-plane
			dq.push_back(H[i]);
			++len;
		}

		// Final cleanup: Check half-planes at the front against the back and vice-versa
		while (len > 2 && dq[0].out(inter(dq[len-1], dq[len-2]))) {
			dq.pop_back();
			--len;
		}

		while (len > 2 && dq[len-1].out(inter(dq[0], dq[1]))) {
			dq.pop_front();
			--len;
		}

		// Report empty intersection if necessary
		if (len < 3) return vector<Point>();

		// Reconstruct the convex polygon from the remaining half-planes.
		vector<Point> ret(len);
		for(int i = 0; i+1 < len; i++) {
			ret[i] = inter(dq[i], dq[i+1]);
		}
		ret.back() = inter(dq[len-1], dq[0]);
		return ret;
	}
}

//check if a is dominated by b and c
bool naiveCheck(cpalgo::Halfplane a, cpalgo::Halfplane b, cpalgo::Halfplane c) {
	return a.out(inter(b, c));
}

void test_check(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto a = Random::line(range);
		auto b = Random::line(range);
		auto c = b;
		while (cross(b[0] - b[1], c[0] - c[1]) == 0) c = Random::line(range);
		
		bool got = hp(a[0], a[1]).check(hp(b[0], b[1]), hp(c[0], c[1]));
		bool expected = naiveCheck(a, b, c);

		if (got != expected) {
			cout << tries << endl;
			cout << a[0] << " " << a[1] << endl;
			cout << b[0] << " " << b[1] << endl;
			cout << c[0] << " " << c[1] << endl;
			cout << boolalpha << got << " " << expected << endl;
			cerr << "error" << FAIL;
		}
		queries++;
	}
	cerr << "tested random queries: " << queries << endl;
}

void stress_test(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		auto centre = Random::point<ll>(-range / 2, range / 2);
		int n = Random::integer<int>(3, 30);

		vector<hp> hps1 = {//+cpalgo bounding box
			{pt( 1e9,  1e9), pt(-1e9,  1e9)},
			{pt(-1e9,  1e9), pt(-1e9, -1e9)},
			{pt(-1e9, -1e9), pt( 1e9, -1e9)},
			{pt( 1e9, -1e9), pt( 1e9,  1e9)},
		};

		vector<cpalgo::Halfplane> hps2;
		for (int i = 0; i < n; i++) {
			auto [a, b] = Random::line(range);
			if (cross(a, b, centre) < 0) swap(a, b);
			hps1.emplace_back(a, b);
			hps2.emplace_back(a, b);
		}

		auto expected = cpalgo::hp_intersect(hps2);
		auto gotHp = intersect(hps1);
		if (sz(gotHp) == 1) cerr << "WHAT?" << FAIL;
		for (hp h : gotHp) {
			if (h.dummy()) cerr << "DUMMY!" << FAIL;//we added a bounding box...
		}
		vector<cpalgo::Point> got;
		if (!gotHp.empty()) {
			gotHp.push_back(gotHp[0]);
			for (int i = 0; i + 1 < sz(gotHp); i++) {
				got.push_back(inter(cpalgo::Halfplane(gotHp[i]), cpalgo::Halfplane(gotHp[i + 1])));
			}
		}

		bool eq = sz(got) == sz(expected);
		for (ll i = 0; eq && i < sz(got); i++) {
			eq &= float_error(got[i].x, expected[i].x) < 1e-6;
			eq &= float_error(got[i].y, expected[i].y) < 1e-6;
		}

		if (!eq) {
			cerr << tries << endl;
			cerr << setprecision(20) << endl;
			for (auto tmp : hps2) cerr << tmp << endl;
			cerr << endl;
			for (auto tmp : expected) cerr << tmp << endl;
			cerr << endl;
			for (auto tmp : got) cerr << tmp << endl;
			cerr << FAIL;
		}
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

/*constexpr int N = 1'000'000;
void performance_test() {
	timer t;
	hash_t hash = 0;
	double maxTime = 0;

	vector<pt> ps;
	for (int i = 0; i*i <= N; i++) {
		for (int j = 0; j*j <= N; j++) {
			ps.emplace_back(i, j);
		}
	}
	t.start();
	hash = shortestDist(ps);
	t.stop();
	maxTime = max(maxTime, t.time);

	ps = Random::points<ll>(N, -1'000'000'000, 1'000'000'000);
	t.reset();
	t.start();
	hash += shortestDist(ps);
	t.stop();
	maxTime = max(maxTime, t.time);

	if (maxTime > 500) cerr << "too slow: " << maxTime << FAIL;
	cerr << "tested performance: " << maxTime << "ms (hash: " << hash << ")" << endl;
}*/

int main() {
	test_check(10);
	test_check(100);
	stress_test(10);
	stress_test(100);
	//performance_test();
}
