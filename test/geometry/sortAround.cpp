#include "../util.h"
constexpr ll EPS = 0;
#define double ll
#define polar polar<ll>
#include <geometry/formulas.cpp>
#undef polar
#undef double
#include <geometry/sortAround.cpp>

//expected order:
//1 8 7
//2 . 6
//3 4 5
void test_tiny() {
	vector<pt> expected = {
		{-1, 1},
		{-1, 0},
		{-1,-1},
		{ 0,-1},
		{ 1,-1},
		{ 1, 0},
		{ 1, 1},
		{ 0, 1},
	};
	auto got = expected;
	for (int i = 0; i < 100'000; i++) {
		shuffle(all(got), Random::rng);
		sortAround(0, got);
		if (got != expected) cerr << "error" << FAIL;
	}
	cerr << "tested tiny" << endl;
}

void stress_test(ll range) {
	ll queries = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		int n = Random::integer<int>(2, 100);
		auto ps = Random::points<ll>(n, -range, range);

		auto contains = [&](pt p){
			for (pt pp : ps) if (pp == p) return true;
			return false;
		};

		pt c;
		do {
			c = Random::point<ll>(-range, range);
		} while (contains(c));

		sortAround(c, ps);

		auto isLeft = [&](pt p){return real(p - c) < 0 || (real(p - c) == 0 && imag(p - c) < 0);};
		auto isCCW = [&](pt a, pt b){return cross(c, a, b) > 0;};
		if (!is_partitioned(all(ps), isLeft)) cerr << "error 1" << FAIL;
		auto mid = partition_point(all(ps), isLeft);
		if (!is_sorted(ps.begin(), mid, isCCW)) cerr << "error 2" << FAIL;
		if (!is_sorted(mid, ps.end(), isCCW)) cerr << "error 3" << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 2'000'000;
void performance_test() {
	timer t;
	auto ps = Random::points<ll>(N, -1'000'000'000, 1'000'000'000);

	t.start();
	sortAround(0, ps);
	t.stop();

	hash_t hash = 0;
	for (pt p : ps) hash += real(p) * imag(p);
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	test_tiny();
	stress_test(100);
	stress_test(1'000'000'000);
	performance_test();
}
