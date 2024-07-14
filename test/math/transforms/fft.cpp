#include "../../util.h"
#include <math/transforms/fft.cpp>

vector<cplx> to_cplx(const vector<ll>& in) {
	vector<cplx> res(sz(in));
	for (int i = 0; i < sz(in); i++) res[i] = in[i];
	return res;
}

vector<ll> from_cplx(const vector<cplx>& in) {
	vector<ll> res(sz(in));
	for (int i = 0; i < sz(in); i++) res[i] = llround(real(in[i]));
	return res;
}

void stress_test() {
	ll queries = 0;
	for (ll i = 0; i < 10'000; i++) {
		int n = 1ll << Random::integer<int>(0, 10);
		auto expected = Random::integers<ll>(n, -1000, 1000);
		vector<cplx> tmp = to_cplx(expected);
		fft(tmp, false);
		fft(tmp, true);
		auto got = from_cplx(tmp);
		if (got != expected) cerr << "error" << FAIL;
		queries += n;
	}
	cerr << "tested queries: " << queries << endl;
}

constexpr int N = 1ll << 21;
void performance_test() {
	timer t;
	auto a = to_cplx(Random::integers<ll>(N, -1000, 1000));
	auto b = to_cplx(Random::integers<ll>(N, -1000, 1000));
	t.start();
	fft(a, true);
	fft(b, false);
	t.stop();
	hash_t hash = 0;
	for (ll i = 0; i < N; i++) hash += i * llround(real(a[i]));
	for (ll i = 0; i < N; i++) hash += i * llround(real(b[i]));
	if (t.time > 500) cerr << "too slow: " << t.time << FAIL;
	cerr << "tested performance: " << t.time << "ms (hash: " << hash << ")" << endl;
}

int main() {
	stress_test();
	performance_test();
}

