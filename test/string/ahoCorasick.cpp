#include "../util.h"
#include <string/ahoCorasick.cpp>

vector<ll> naive(string s, vector<string> patterns) {
    vector<ll> ans(patterns.size());
    for (int k = 0; k < (int)patterns.size(); k++) {
        string pattern = patterns[k];
        for (int i = 0; i + pattern.size() <= s.size(); i++) {
            if (s.substr(i, pattern.size()) == pattern) ans[k]++;
        }
    }
    return ans;
}

vector<ll> normal(string s, vector<string> patterns) {
    AhoCorasick aho;
    vector<int> ind(patterns.size());
    for (int i = 0; i < (int)patterns.size(); i++) {
        ind[i] = aho.addString(patterns[i]);
    }
    aho.buildGraph();

    int v = 0;
    for (char c : s) v = aho.go(v, c - OFFSET), aho.dp[v]++;
    aho.dfs();
    vector<ll> ans(patterns.size());
    for (int i = 0; i < (int)patterns.size(); i++) {
        ans[i] = aho.dp[ind[i]];
    }
    return ans;
}

void stress_test() {
    ll queries = 0;
    for (int i = 0; i < 100; i++) {
        int n = Random::integer(1, 100);
        string s = Random::string(n, "abc");
        int m = Random::integer(1, 100);
        vector<string> patterns(m);
        for (string& e : patterns) {
            int k = Random::integer(1, 100);
            e = Random::string(k, "abc");
        }

        auto got = normal(s, patterns);
        auto expected = naive(s, patterns);
        if (got != expected) cerr << "Wrong Answer" << FAIL;
        queries++;
    }
    cerr << "Tested random queries: " << queries << endl;
}

constexpr int N = 1'000'000;
void performance_test() {
    timer t;
    string s = string(N, 'a') + Random::string(N, "ab");
    vector<string> patterns = {"a"};
    for (int sm = 1; sm < N; sm += patterns.back().size()) {
        patterns.emplace_back(patterns.back().size()+1, 'a');
    }
    for (int i = 0; i < 100; i++) {
        patterns.emplace_back(Random::string(N/100, "ab"));
    }

    t.start();
    hash_t hash = normal(s, patterns)[0];
    t.stop();

    if (t.time > 500) cerr << "Too slow: " << t.time << FAIL;
    cerr << "Tested performance: " << t.time << "ms (hash: hash " << hash << ")" << endl;
}

int main() {
    stress_test();
    performance_test();
}
