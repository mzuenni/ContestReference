vector<mat> pows;

void precalc(mat m) {
	pows = {mat(sz(m.m), 1), m};
	for (int i = 1; i < 60; i++) pows.push_back(pows[i] * pows[i]);
}

auto calc(ll b, vector<ll> v) {
	for (ll i = 1; b > 0; i++) {
		if (b & 1) v = pows[i] * v;
		b /= 2;
	}
	return v;
}
