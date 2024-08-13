#include "../util.h"
constexpr double EPS = 1e-9;
constexpr int UNIQUE = 1;
constexpr int INCONSISTENT = 2;
constexpr int MULTIPLE = 3;
vector<vector<double>> mat;
#include <math/gauss.cpp>

vector<vector<double>> inverseMat(const vector<vector<double>>& m) {
	int n = sz(m);
	mat = m;
	for (int i = 0; i < n; i++) {
		if (sz(mat[i]) != n) cerr << "error: no square matrix" << FAIL;
		mat[i].resize(2*n);
		mat[i][n+i] = 1;
	}
	gauss(n); //the unique cetc. checks are not usefull since we dont solve an lgs...
	vector<vector<double>> res(m);
	for (int i = 0; i < n; i++) {
		res[i] = vector<double>(mat[i].begin() + n, mat[i].end());
		for (int j = 0; j < n; j++) {
			if (j != i && mat[i][j] != 0) cerr << "error: not full rank?" << FAIL;
			if (j == i && mat[i][j] == 0) cerr << "error: not full rank?" << FAIL;
		}
	}
	return res;
}

vector<vector<double>> mul(const vector<vector<double>>& a, const vector<vector<double>>& b) {
	int n = sz(a);
	int m = sz(b[0]);
	int x = sz(b);
	if (sz(a[0]) != sz(b)) cerr << "error: wrong dimensions" << FAIL;
	vector<vector<double>> res(n, vector<double>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < x; k++) {
				res[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return res;
}

void test_tiny() {
	mat = {
		{1, 2, 3, 4},
		{0, 5, 6, 7},
		{0, 0, 8, 9},
	};
	if (gauss(sz(mat)) != UNIQUE) cerr << "error: 1" << FAIL;

	mat = {
		{-1,  1, 0, -1},
		{ 2,  6, 0, 10},
		{ 1, -2, 0,  0},
	};
	if (gauss(sz(mat)) != MULTIPLE) cerr << "error: 2" << FAIL;

	mat = {
		{-1,  1, 0, -1},
		{ 2,  6, 0, 10},
		{ 1, -2, 0,  1},
	};
	if (gauss(sz(mat)) != INCONSISTENT) cerr << "error: 3" << FAIL;
}

void stress_test_inv() {
	ll queries = 0;
	for (int tries = 0; tries < 20'000; tries++) {
		int n = Random::integer<int>(1, 30);

		vector<vector<double>> m(n);
		for (auto& v : m) v = Random::reals<double>(n, 0, 1'000);
		// m hopefully has full rank...

		auto inv = inverseMat(m);

		auto prod = mul(m, inv);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j && abs(prod[i][j] - 1) >= EPS) cerr << "error: not inverted " << prod[i][j] << FAIL;
				if (i != j && abs(prod[i][j] - 0) >= EPS) cerr << "error: not inverted " << prod[i][j] << FAIL;
			}
		}

		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 250;
void performance_test() {
	timer t;

	vector<vector<double>> m(N);
	for (auto& v : m) v = Random::reals<double>(N, 0, 1'000);
	mat = m;

	t.start();
	gauss(N);
	t.stop();
	hash_t hash = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			hash += mat[i][j];
		}
	}
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	test_tiny();
	stress_test_inv();
	performance_test();
}
