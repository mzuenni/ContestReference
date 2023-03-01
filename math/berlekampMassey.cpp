constexpr ll mod = 1'000'000'007;
vector<ll> BerlekampMassey(const vector<ll>& s) {
	int n = sz(s), L = 0, m = 0;
	vector<ll> C(n), B(n), T;
	C[0] = B[0] = 1;

	ll b = 1;
	for (int i = 0; i < n; i++) {
		m++;
		ll d = s[i] % mod;
		for (int j = 1; j <= L; j++) {
			d = (d + C[j] * s[i - j]) % mod;
		}
		if (!d) continue;
		T = C;
		ll coef = d * powMod(b, mod-2, mod) % mod;
		for (int j = m; j < n; j++) {
			C[j] = (C[j] - coef * B[j - m]) % mod;
		}
		if (2 * L > i) continue;
		L = i + 1 - L;
		swap(B, T);
		b = d;
		m = 0;
	}

	C.resize(L + 1);
	C.erase(C.begin());
	for (auto& x : C) x = (mod - x) % mod;
	return C;
}
