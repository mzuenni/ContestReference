#include <bits/stdc++.h>
using namespace std;

#define all(x) ::begin(x), ::end(x)
#define sz(x) (ll)::size(x)

using ll = long long;
using lll = __int128;
using ld = long double;
using pt = complex<ll>;

namespace INT {constexpr int INF = 0x3FFF'FFFF;}
namespace LL {constexpr ll INF = 0x3FFF'FFFF'FFFF'FFFFll;}
namespace LD {constexpr ld INF = numeric_limits<ld>::infinity();}

namespace Random {
	mt19937_64 rng(3141592653589793238ll);
	template<typename T = ll>
	T integer(T l, T r) {
		return uniform_int_distribution<T>(l, r-1)(rng);
	}

	template<typename T = ll>
	T integer(T r) {
		return integer(0, r);
	}

	template<typename T = ll>
	std::pair<T, T> pair(T l, T r) {
		T a = integer(l, r);
		T b = integer(l, r);
		if (a > b) swap(a, b);
		return {a, b};
	}

	template<typename T = ll>
	std::pair<T, T> pair(T r) {
		return pair(0, r);
	}
}

[[noreturn]] ostream& FAIL(ostream& os) {
	os << endl;
	exit(1);
}

struct timer {
	bool running = false;
	double time = 0;
	chrono::steady_clock::time_point begin;

	void start() {
		if (running) cerr << "timer already running!" << FAIL;
		running = true;
		begin = chrono::steady_clock::now();
	}

	void stop() {
		auto end = chrono::steady_clock::now();
		if (!running) cerr << "timer not running!" << FAIL;
		running = false;
		time += chrono::duration_cast<chrono::duration<double, milli>>(end - begin).count();
	}

	~timer() {
		if (running) cerr << "timer not stopped!" << FAIL;
	}
};
