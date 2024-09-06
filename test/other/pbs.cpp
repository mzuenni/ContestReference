#include "../util.h"

struct Union {
    vector<int> a;

    Union(int n) : a(n, -1) {}

    int find(int i) {
        return a[i] < 0 ? i : a[i] = find(a[i]);
    }

    void join(int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return;
        a[j] = i;
    }

    bool same(int i, int j) {
        return find(i) == find(j);
    }
};

int n;
Union un(0);
void reset() {
    un = Union(n);
}

vector<pair<int, int>> edges;
void do_step(int i) {
    auto [u, v] = edges[i];
    un.join(u, v);
}

vector<pair<int, int>> queries;
bool test(int i) {
    auto [u, v] = queries[i];
    return un.same(u, v);
}

#include <other/pbs.cpp>
void stress_test() {
	for (int it = 0; it < 100'000; it++) {
        n = Random::integer(2, 31);
        int Q = Random::integer(2, 31);
        int MAX_OPERATIONS = n-1;

        edges.clear();
        for (int i=1; i<n; i++) {
            edges.emplace_back(Random::integer(0, i), i);
        }
        shuffle(all(edges), Random::rng);
        queries.clear();
        for (int i=0; i<Q; i++) {
            auto x = Random::distinct(2, n);
            queries.emplace_back(x[0], x[1]);
        }
        vector<int> ans = pbs(Q, MAX_OPERATIONS);

        vector<int> correct(Q, -1);
        Union un2(n);
        for (int j=0; j<MAX_OPERATIONS; j++) {
            un2.join(edges[j].first, edges[j].second);
            for (int k=0; k<Q; k++) if (correct[k] == -1) {
                if (un2.same(queries[k].first, queries[k].second)) {
                    correct[k] = j;
                }
            }
        }

        if (ans != correct) cerr << "Failed stress test" << FAIL;
	}
}

void performance_test() {
    n = 300'000;
    constexpr int Q = 300'000;
    int MAX_OPERATIONS = n-1;
    edges.clear();
    for (int i=1; i<n; i++) {
        edges.emplace_back(Random::integer(0, i), i);
    }
    shuffle(all(edges), Random::rng);
    queries.clear();
    for (int i=0; i<Q; i++) {
        auto x = Random::distinct(2, n);
        queries.emplace_back(x[0], x[1]);
    }

    timer t;
    t.start();
    vector<int> ans = pbs(Q, MAX_OPERATIONS);
    t.stop();
    ll hash = accumulate(all(ans), 0LL);

	if (t.time > 700) cerr << "too slow: " << t.time << FAIL;
    cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
    stress_test();
    performance_test();
}
