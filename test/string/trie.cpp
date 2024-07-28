#include "../util.h"
#include <string/trie.cpp>

void stress_test() {
	multiset<vector<int>> naive;
	ll queries = 0;
	ll deleted = 0;
	for (int tries = 0; tries < 100'000; tries++) {
		{
			int n = Random::integer<int>(1, 20);
			auto s = Random::integers<int>(n, 0, 2);
			insert(s);
			naive.insert(s);
		}
		{
			int n = Random::integer<int>(1, 20);
			auto s = Random::integers<int>(n, 0, 2);
			bool got = erase(s);
			auto it = naive.find(s);
			bool expected = it != naive.end();
			if (expected) naive.erase(it);
			if (got != expected) cerr << "error" << FAIL;
			queries++;
			if (got) deleted++;
		}
	}
	cerr << "tested random queries: " << queries << " (" << deleted << ")" << endl;
}

constexpr int N = 10'000;
void performance_test() {
	timer t;
	trie = {node()};
	hash_t hash = 0;
	for (int tries = 0; tries < N; tries++) {
		{
			int n = Random::integer<int>(1, 2000);
			auto s = Random::integers<int>(n, 0, 2);
			t.start();
			insert(s);
			t.stop();
		}
		{
			int n = Random::integer<int>(1, 2000);
			auto s = Random::integers<int>(n, 0, 2);
			t.start();
			hash += erase(s);
			t.stop();
		}
	}
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}
