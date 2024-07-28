#include "../util.h"
#include <graph/scc.cpp>
#define static vector<vector<int>> adj; static // hacky...
#include <graph/2sat.cpp>
#undef static
#undef adj

struct RandomClause {
	int a, b;
	int type;
	RandomClause(int n) :
		a(Random::integer<int>(0, 2*n)),
		b(Random::integer<int>(0, 2*n)),
		type(Random::integer<int>(0, 8)) {}

	bool eval(vector<int>& sol) const {
		bool ba = sol[a];
		bool bb = sol[b];
		if (type == 0) return !ba || bb;
		if (type == 1) return ba == bb;
		if (type == 2) return ba || bb;
		if (type == 3) return ba != bb;
		if (type == 4) return ba && bb;
		if (type == 5) return !(ba && bb);

		if (type == 6) return ba;
		if (type == 7) return !ba;
		return false;
	}

	void add(sat2& sat) const {
		int va = a;
		int vb = b;
		if (type == 0) sat.addImpl(va, vb);
		if (type == 1) sat.addEquiv(va, vb);
		if (type == 2) sat.addOr(va, vb);
		if (type == 3) sat.addXor(va, vb);
		if (type == 4) sat.addAnd(va, vb);
		if (type == 5) sat.addNand(va, vb);

		if (type == 6) sat.addTrue(va);
		if (type == 7) sat.addFalse(va);
	}

	friend ostream& operator<<(ostream& os, const RandomClause& c) {
		if (c.a & 1) os << "-";
		os << (c.a >> 1);
		if (c.type == 0) os << "=>";
		if (c.type == 1) os << "==";
		if (c.type == 2) os << "or";
		if (c.type == 3) os << "xor";
		if (c.type == 4) os << "and";
		if (c.type == 5) os << "nand";

		if (c.type == 6) return os;
		if (c.type == 7) return os << "==F";

		if (c.b & 1) os << "-";
		os << (c.b >> 1);
		return os;
	}
};

bool naive(int n, const vector<RandomClause>& clauses) {
	for (ll i = 0; i < (1ll << n); i++) {
		vector<int> tmp(2*n);
		for (ll j = 0; j < n; j++) {
			tmp[(2*j) + ((i >> j) & 1)] = 1;
		}
		bool ok = true;
		for (auto& c : clauses) ok &= c.eval(tmp);
		if (ok) return true;
	}
	return false;
}

void stress_test() {
	ll queries = 0;
	for (int tries = 0; tries < 200'000; tries++) {
		int n = Random::integer<int>(1, 12);
		int m = Random::integer<int>(0, 30);

		vector<RandomClause> clauses;
		for (int i = 0; i < m; i++) clauses.emplace_back(n);

		sat2 sat(n);
		for (auto& c : clauses) c.add(sat);
		adj = sat.adj;

		bool got = sat.solve();
		bool expected = naive(n, clauses);

		if (got) {
			for (int i = 0; i < 2*n; i+=2) {
				if (sat.sol[i] < 0) cerr << "error: invalid vars" << FAIL;
				if (sat.sol[i+1] < 0) cerr << "error: invalid vars" << FAIL;
				if (sat.sol[i] == sat.sol[i+1]) cerr << "error: inconsistent vars" << FAIL;
			}
			for (auto& c : clauses) {
				if (!c.eval(sat.sol)) {
					cerr << "error: inconsistent" << FAIL;
				}
			}
		}

		if (got != expected) cerr << "got: " << got << ", expected: " << expected << FAIL;
		queries += n;
	}
	cerr << "tested random queries: " << queries << endl;
}

constexpr int N = 200'000;
constexpr int M = 500'000;
void performance_test() {
	timer t;
	vector<RandomClause> clauses;
	for (int i = 0; i < M; i++) clauses.emplace_back(N);
	t.start();
	sat2 sat(N);
	for (auto& c : clauses) c.add(sat);
	t.stop();
	adj = sat.adj;
	t.start();
	hash_t hash = sat.solve();
	t.stop();
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
