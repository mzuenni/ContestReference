constexpr ll mod = 998244353;
// oder ntt mul @\sourceref{math/transforms/ntt.cpp}@
vector<ll> mul(const vector<ll>& a, const vector<ll>& b) {
	vector<ll> c(sz(a) + sz(b) - 1);
	for (int i = 0; i < sz(a); i++) {
		for (int j = 0; j < sz(b); j++) {
			c[i+j] += a[i]*b[j] % mod;
	}}
	for (ll& x : c) x %= mod;
	return c;
}

ll kthTerm(const vector<ll>& f, const vector<ll>& c, ll k) {
	int n = sz(c);
	vector<ll> q(n + 1, 1);
	for (int i = 0; i < n; i++) q[i + 1] = (mod - c[i]) % mod;
	vector<ll> p = mul(f, q);
	p.resize(n);
	p.push_back(0);
	do {
		vector<ll> q2 = q;
		for (int i = 1; i <= n; i += 2) q2[i] = (mod - q2[i]) % mod;
		vector<ll> x = mul(p, q2), y = mul(q, q2);
		for (int i = 0; i <= n; i++){
			p[i] = i == n ? 0 : x[2*i + (k&1)];
			q[i] = y[2*i];
		}
	} while (k /= 2);
	return p[0];
}
