#include <bits/stdc++.h>
using namespace std;

#define all(x) ::begin(x), ::end(x)
#define sz(x) (ll)::size(x)

using ll = long long;
using lll = __int128;
using ld = long double;
using hash_t = unsigned long long;

namespace INT {constexpr int INF = 0x3FFF'FFFF;}
namespace LL {constexpr ll INF = 0x3FFF'FFFF'FFFF'FFFFll;}
namespace LD {constexpr ld INF = numeric_limits<ld>::infinity();}

namespace details {
	template<typename T = ll>
	bool isPrime(T x) {
		for (T i = 2; i*i <= x; i++) {
			if (x % i == 0) return false;
		}
		return x > 1;
	}
}

namespace Random {
	mt19937_64 rng(3141592653589793238ll);
	template<typename T = ll>
	T integer(T l, T r) {
		return uniform_int_distribution<T>(l, r-1)(rng);
	}

	template<typename T = ll>
	T integer(T r) {
		return integer<T>(0, r);
	}

	template<typename T = ll>
	std::vector<T> integers(std::size_t n, T l, T r) {
		std::vector<T> res(n);
		for (T& x : res) x = integer<T>(l, r);
		return res;
	}

	template<typename T = ll>
	std::vector<T> integers(std::size_t n, T r) {
		return integers<T>(n, 0, r);
	}

	template<typename T = ll>
	std::pair<T, T> pair(T l, T r) {
		T a = integer<T>(l, r);
		T b = integer<T>(l, r);
		if (a > b) swap(a, b);
		return {a, b};
	}

	template<typename T = ll>
	std::pair<T, T> pair(T r) {
		return pair<T>(0, r);
	}

	std::string string(std::size_t n, string_view chars) {
		std::string res(n, '*');
		for (char& c : res) c = chars[integer(sz(chars))];
		return res;
	}

	template<typename T = ll>
	T prime(T l, T r) {
		T res = 0;
		do {
			res = integer<T>(l, r);
		} while (!details::isPrime<T>(res));
		return res;
	}

	template<typename T = ll>
	T prime(T r) {
		return prime<T>(2, r);
	}

	template<typename T = ll, typename std::enable_if<!std::is_floating_point<T>::value>::type* = nullptr>
	std::complex<T> point(T l, T r) {
		return {integer<T>(l, r), integer<T>(l, r)};
	}

	template<typename T = ll, typename std::enable_if<!std::is_floating_point<T>::value>::type* = nullptr >
	std::complex<T> point(T r) {
		return point<T>(0, r);
	}

	template<typename T = ll, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
	std::complex<T> point(T l, T r) {
		uniform_real_distribution<T> dist(l, r);
		return {dist(rng), dist(rng)};
	}

	template<typename T = ll, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr >
	std::complex<T> point(T r) {
		return point<T>(0, r);
	}

	template<typename T = ll, typename std::enable_if<!std::is_floating_point<T>::value>::type* = nullptr>
	std::vector<std::complex<T>> points(std::size_t n, T l, T r) {
		std::vector<std::complex<T>> res(n);
		for (auto& x : res) x = point<T>(l, r);
		return res;
	}

	template<typename T = ll, typename std::enable_if<!std::is_floating_point<T>::value>::type* = nullptr >
	std::vector<std::complex<T>> points(std::size_t n, T r) {
		return points<T>(n, 0, r);
	}

	template<typename T = ll, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
	std::vector<std::complex<T>> points(std::size_t n, T l, T r) {
		std::vector<std::complex<T>> res(n);
		for (auto& x : res) x = point<T>(l, r);
		return res;
	}

	template<typename T = ll, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr >
	std::vector<std::complex<T>> points(std::size_t n, T r) {
		return points<T>(n, 0, r);
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

	void reset() {
		running = false;
		time = 0;
	}

	~timer() {
		if (running) cerr << "timer not stopped!" << FAIL;
	}
};

namespace c20 {
	namespace detail {
		template<class T, std::size_t N, std::size_t... I>
		constexpr std::array<std::remove_cv_t<T>, N> to_array_impl(T (&a)[N], std::index_sequence<I...>) {
			return {{a[I]...}};
		}
	}
 
	template<class T, std::size_t N>
	constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&a)[N]) {
		return c20::detail::to_array_impl(a, std::make_index_sequence<N>{});
	}
}
