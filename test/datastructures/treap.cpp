#include "../util.h"
#include <datastructures/treap.cpp>

void add(Treap& t, vector<ll>& ans, int v) {
    if (v < 0) return;
    add(t, ans, t.treap[v].l);
    ans.push_back(t.treap[v].val);
    add(t, ans, t.treap[v].r);
}

vector<ll> to_vec(Treap& t) {
    vector<ll> ans;
    add(t, ans, t.root);
    return ans;
}

void stress_test(int T, int n) {
	for (int tries = 0; tries < T; tries++) {
		int ins = Random::integer<int>(1, n);
        int rem = Random::integer<int>(0, ins+1);

        vector<ll> a;
        Treap t;
        while (ins + rem > 0) {
            bool is_ins = Random::integer(0, ins+rem) < ins;
            if (a.empty()) is_ins = true;

            if (is_ins) {
                int ind = Random::integer<int>(0, (int)sz(a)+1);
                ll val = Random::integer((ll)-1e18, (ll)1e18+1);
                t.insert(ind, val);
                a.insert(a.begin() + ind, val);
                ins--;
            } else {
                int ind = Random::integer<int>(0, (int)sz(a));
                int cnt = Random::integer<int>(1, 1 + min<int>({(int)sz(a)-ind, rem, (int)sqrt(n)}));
                t.remove(ind, cnt);
                a.erase(a.begin() + ind, a.begin() + ind + cnt);
                rem -= cnt;
            }
        }
        if (to_vec(t) != a) cerr << "Failed stress test" << FAIL;
	}
	cerr << "Tested " << T << " random tests with n<=" << n << endl;
}

constexpr int N = 200'000;
void performance_test() {
	timer t;

	t.start();
	Treap tr;
	t.stop();

	hash_t hash = 0;
	for (int operations = 0; operations < N; operations++) {
        int ind = Random::integer<int>(0, operations+1);
        ll val = Random::integer((ll)-1e18, (ll)1e18+1);

		t.start();
        tr.insert(ind, val);
		hash ^= tr.root;
		t.stop();
	}
    while (tr.root != -1) {
        t.start();
        int sz = tr.getSize(tr.root);
        t.stop();

        int ind = Random::integer<int>(0, sz);
        int cnt = Random::integer<int>(1, 1 + min<int>(sz-ind, 10));
        t.start();
        tr.remove(ind, cnt);
        t.stop();
    }
	if (t.time > 1000) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test(10000, 10);
	stress_test(1000, 100);
	stress_test(100, 10000);
	performance_test();
}
