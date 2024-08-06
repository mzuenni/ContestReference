#include "../util.h"
constexpr ll INF = LL::INF;
#include <other/divideAndConquer.cpp>

vector<vector<ll>> gen(int n) {
	vector<vector<ll>> res(n, vector<ll>(n));
	ll mi = 0;
	for (ll a = n-1; a >= 0; a--) {
		for (ll c = n-1; c >= a; c--) {
			for (ll b = a; b <= c; b++) {
				for (ll d = c; d < n; d++) {
					res[a][c] = min(res[a][c], res[a][d] + res[b][c] - res[b][d]);
				}
			}
			res[a][c] -= Random::integer<ll>(0, 1000);
			mi = min(mi, res[a][c]);
		}
	}
	for (auto& v : res) for (auto& x : v) x -= mi;
	
	for (ll a = 0; a < n; a++) {
		for (ll b = a; b < n; b++) {
			for (ll c = b; c < n; c++) {
				for (ll d = c; d < n; d++) {
					if (res[a][d] < 0 || res[a][d] + res[b][c] < res[a][c] + res[b][d]) {
						 cerr << "invalid C array!" << FAIL;
					}
				}
			}
		}
	}
	return res;
}

vector<vector<ll>> genQuick(int n) {
	vector<vector<ll>> res(n, vector<ll>(n));
	for (ll a = n-1; a >= 0; a--) {
		for (ll c = n-1; c >= a; c--) {
			res[a][c] = (c-a) * (c - a) + Random::integer<ll>(0, 2);
		}
	}
	return res;
}

/*ll naive(int n, int m) {
	vector<vector<ll>> state(m+1, vector<ll>(n+1, INF));
	state[0][0] = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= j; k++) {
				state[i][j] = min(state[i][j], state[i-1][k-1] + C[k-1][j-1]);
			}
		}
	}
	return state[m][n];
}*/

vector<ll> naive(int n) {
	vector<vector<ll>> state(n+1, vector<ll>(n+1, INF));
	state[0][0] = 0;
	vector<ll> res(n+1, INF);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			for (int k = 1; k <= j; k++) {
				state[i][j] = min(state[i][j], state[i-1][k-1] + C[k-1][j-1]);
			}
		}
		res[i] = state[i][n];
	}
	return res;
}

void stress_test() {
	ll tests = 0;
	for (ll i = 0; i < 1000; i++) {
		auto n = Random::integer(10, 20);
		C = gen(n);
		auto expected = naive(n);
		for (ll m = 1; m <= n; m++) {
			auto got = calc(n, m);
			if (got != expected[m]) cerr << "got: " << got << ", expected: " << expected[m] << FAIL;
			tests++;
		}
	}
	cerr << "tested random queries: " << tests << endl;
}

constexpr int N = 10'000;
void performance_test() {
	timer t;
	C = genQuick(N);
	t.start();
	auto hash = calc(N, 32);
	t.stop();
	if (t.time > 50) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

