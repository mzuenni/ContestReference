vector<ll> poly_inv(const vector<ll>& a, int n) {
	vector<ll> q = {powMod(a[0], mod-2, mod)};
	for (int len = 1; len < n; len *= 2){
		vector<ll> a2 = a, q2 = q;
		a2.resize(2*len), q2.resize(2*len);
		ntt(q2);
		for (int _ : {0, 1}) {
			ntt(a2);
			for (int i = 0; i < 2*len; i++) a2[i] = a2[i]*q2[i] % mod;
			ntt(a2, true);
			for (int i = 0; i < len; i++) a2[i] = 0;
		}
		for (int i = len; i < min(n, 2*len); i++) {
			q.push_back((mod - a2[i]) % mod);
	}}
	return q;
}

vector<ll> poly_deriv(vector<ll> a) {
	for (int i = 1; i < sz(a); i++)
		a[i-1] = a[i] * i % mod;
	a.pop_back();
	return a;
}

vector<ll> poly_integr(vector<ll> a) {
	static vector<ll> inv = {0, 1};
	for (static int i = 2; i <= sz(a); i++)
		inv.push_back(mod - mod / i * inv[mod % i] % mod);

	a.push_back(0);
	for (int i = sz(a) - 1; i > 0; i--)
		a[i] = a[i-1] * inv[i] % mod;
	a[0] = 0;
	return a;
}

vector<ll> poly_log(vector<ll> a, int n) {
	a = mul(poly_deriv(a), poly_inv(a, n));
	a.resize(n-1);
	return poly_integr(a);
}

vector<ll> poly_exp(vector<ll> a, int n) {
	vector<ll> q = {1};
	for (int len = 1; len < n; len *= 2) {
		vector<ll> p = poly_log(q, 2*len);
		for (int i = 0; i < 2*len; i++)
			p[i] = (mod - p[i] + (i < sz(a) ? a[i] : 0)) % mod;
		vector<ll> q2 = q;
		q2.resize(2*len);
		ntt(p), ntt(q2);
		for (int i = 0; i < 2*len; i++) p[i] = p[i] * q2[i] % mod;
		ntt(p, true);
		for (int i = len; i < min(n, 2*len); i++) q.push_back(p[i]);
	}
	return q;
}
