#include <bits/stdc++.h>
using namespace std;

#define all(x) std::begin(x), std::end(x)
#define sz(x) (ll)std::size(x)

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

	template<typename T = ld>
	T real(T l, T r) {
		return uniform_real_distribution<T>(l, r)(rng);
	}

	template<typename T = ld>
	T real(T r) {
		return real<T>(0, r);
	}

	template<typename T = ld>
	std::vector<T> reals(std::size_t n, T l, T r) {
		std::vector<T> res(n);
		for (T& x : res) x = real<T>(l, r);
		return res;
	}

	template<typename T = ld>
	std::vector<T> reals(std::size_t n, T r) {
		return reals<T>(n, 0, r);
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

	template<typename T = ld, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
	std::complex<T> point(T l, T r) {
		return {real(l, r), real(l, r)};
	}

	template<typename T = ll>
	std::complex<T> point(T r) {
		return point<T>(0, r);
	}

	template<typename T = ll, typename std::enable_if<!std::is_floating_point<T>::value>::type* = nullptr>
	std::vector<std::complex<T>> points(std::size_t n, T l, T r) {
		std::vector<std::complex<T>> res(n);
		for (auto& x : res) x = point<T>(l, r);
		return res;
	}

	template<typename T = ld, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
	std::vector<std::complex<T>> points(std::size_t n, T l, T r) {
		std::vector<std::complex<T>> res(n);
		for (auto& x : res) x = point<T>(l, r);
		return res;
	}

	template<typename T = ll>
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

	friend std::ostream& operator<<(std::ostream& os, const timer& t) {
		if (t.running) cerr << "timer already running!" << FAIL;
		return os << t.time;
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

struct NoData {};

template<typename W = NoData>
struct Edge {
	int from, to;
	mutable W w;

	Edge(int from_, int to_, W w_ = {}) : from(from_), to(to_), w(w_) {}

	template<typename F>
	void forE(int x, F&& f) const {
		int y = from ^ to ^ x;
		if constexpr (is_same_v<W, NoData>) f(x, y);
		else f(x, y, w);
	}

	template<typename F>
	void forE(F&& f) const {
		forE(from, f);
	}

	friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
		os << e.from << "->" << e.to;
		if constexpr (!is_same_v<W, NoData>) os << ": " << e.w;
		return os;
	}
};


template<typename W = NoData, bool DIR = false, bool MULTI = false, bool LOOPS = false>
class Graph {
	vector<multimap<int, int>> adj;
	vector<Edge<W>> edges;

	void _addAdj(int e) {
		adj[edges[e].from].emplace(edges[e].to, e);
		if (!DIR && edges[e].from != edges[e].to) adj[edges[e].to].emplace(edges[e].from, e);
	}
public:

	Graph(int n) : adj(n) {}

	int m() const {return sz(edges);}
	int n() const {return sz(adj);}
	int deg(int x) const {return sz(adj[x]);}

	Graph& clear() {
		adj.assign(adj.size(), {});
		edges.clear();
		return *this;
	}

	bool addEdge(int from, int to, W w = {}) {
		if (!LOOPS && from == to) return false;
		if (!MULTI && adj[from].find(to) != adj[from].end()) return false;
		edges.emplace_back(from, to, w);
		_addAdj(sz(edges) - 1);
		return true;
	}

	Graph& reverse() {
		for (auto& e : edges) swap(e.from, e.to);
		adj.assign(adj.size(), {});
		for (int i = 0; i < sz(edges); i++) _addAdj(i);
		return *this;
	}

	Graph& shuffle() {
		std::shuffle(all(edges), Random::rng);
		if constexpr (!DIR) {
			for (auto& e : edges) {
				if (Random::integer(0, 2)) swap(e.from, e.to);
			}
		}
		adj.assign(adj.size(), {});
		for (int i = 0; i < sz(edges); i++) _addAdj(i);
		return *this;
	}

	Graph& permutate() {
		vector<int> perm(n());
		iota(all(perm), 0);
		std::shuffle(all(perm), Random::rng);
		for (auto& e : edges) {
			e.from = perm[e.from];
			e.to = perm[e.to];
		}
		shuffle();
		return *this;
	}

	template<typename F>
	void forEdges(F&& f) {
		for (auto e : edges) e.forE(f);
	}

	template<typename F>
	void forOut(int x, F&& f) {
		for (auto [_, id] : adj[x]) edges[id].forE(x, f);
	}

	Graph& tree() {
		if (DIR) cerr << "randomTree must be undirected" << FAIL;
		if (n() <= 1) return *this;
		auto code = Random::integers<int>(n()-2, 0, n());
		vector<int> count(n());
		for (int x : code) count[x]++;
		int current = -1;
		int skip = -1;
		auto getNext = [&](){
			int oldSkip = skip;
			skip = -1;
			if (0 <= oldSkip and oldSkip <= current) return oldSkip;
			for (current++; count[current] > 0; current++) {}
			return current;
		};
		for (int x : code) {
			addEdge(x,  getNext());
			count[x]--;
			if (count[x] == 0) skip = x;
		}
		addEdge(getNext(), getNext());
		return *this;
	}

	Graph& star() {
		for (int i = 1; i < n; i++) addEdge(0, i);
		return *this;
	}

	Graph& path() {
		for (int i = 1; i < n; i++) addEdge(i-1, i);
		return *this;
	}

	Graph& erdosRenyi(int todo) {//this could be slow...
		if constexpr (!MULTI) {
			ll lim = (ll)n() * (n() - 1) / 2;
			if constexpr (DIR) lim *= 2;
			if constexpr (LOOPS) lim += n;
			lim -= m();
			if (todo > lim) cerr << "too many edges! n: " << n() << " " << todo << " > " << lim << FAIL;
			if (todo > lim / 2) {
				vector<pair<int, int>> tmp;
				if constexpr(LOOPS) {
					for (int i = 0; i < n(); i++) tmp.emplace_back(i, i);
				}
				for (int i = 0; i < n(); i++) {
					for (int j = 0; j < i; j++) {
						tmp.emplace_back(i, j);
						if constexpr (DIR) tmp.emplace_back(j, i);
					}
				}
				if constexpr (!DIR) {
					for (auto& [a, b] : tmp) {
						if (Random::integer<int>(0, 2) == 0) {
							swap(a, b);
						}
					}
				}
				std::shuffle(all(tmp), Random::rng);
				for (auto [a, b] : tmp) {
					if (todo <= 0) break;
					if (addEdge(a, b)) todo--;
				}
				if (todo > 0) cerr << "too many edges!" << FAIL;
				return *this;
			}
		}
		while (todo > 0) {
			int a = Random::integer(0, n());
			int b = Random::integer(0, n());
			if (addEdge(a, b)) todo--;
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Graph& g) {
		os << g.n() << " " << g.m();
		for (auto& e : g.edges) os << endl << e;
		return os;
	}
};
