constexpr ll mod = 1'000'000'007;
vector<ll> modMul(const vector<ll>& a, const vector<ll>& b,
                  const vector<ll>& c) {
	ll n = sz(c);
	vector<ll> res(n * 2 + 1);
	for (int i = 0; i <= n; i++) { //a*b
		for (int j = 0; j <= n; j++) {
			res[i + j] += a[i] * b[j];
			res[i + j] %= mod;
	}}
	for (int i = 2 * n; i > n; i--) { //res%c
		for (int j = 0; j < n; j++) {
			res[i - 1 - j] += res[i] * c[j];
			res[i - 1 - j] %= mod;
	}}
	res.resize(n + 1);
	return res;
}

ll kthTerm(const vector<ll>& f, const vector<ll>& c, ll k) {
	assert(sz(f) == sz(c));
	vector<ll> tmp(sz(c) + 1), a(sz(c) + 1);
	tmp[0] = a[1] = 1; //tmp = (x^k) % c

	for (k++; k > 0; k /= 2) {
		if (k & 1) tmp = modMul(tmp, a, c);
		a = modMul(a, a, c);
	}

	ll res = 0;
	for (int i = 0; i < sz(c); i++) res += (tmp[i+1] * f[i]) % mod;
	return res % mod;
}
