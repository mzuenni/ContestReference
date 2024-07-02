vector<mat> pows;

void precalc(mat m) {
	pows = {mat(1), m};
	for (int i = 1; i < 60; i++) pows.push_back(pows[i] * pows[i]);
}

ll calc(int x, int y, ll b) {
	vector<ll> v(pows[0].m.size());
	v[x] = 1;
	for (ll i = 1; b > 0; i++) {
		if (b & 1) v = pows[i] * v;
		b /= 2;
	}
	return v[y];
}
