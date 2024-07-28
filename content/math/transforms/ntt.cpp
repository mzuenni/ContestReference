constexpr ll mod = 998244353, root = 3;

void ntt(vector<ll>& a, bool inv = false) {
	int n = sz(a);
	auto b = a;
	ll r = inv ? powMod(root, mod - 2, mod) : root;

	for (int s = n / 2; s > 0; s /= 2) {
		ll ws = powMod(r, (mod - 1) / (n / s), mod), w = 1;
		for (int j = 0; j < n / 2; j += s) {
			for (int k = j; k < j + s; k++) {
				ll u = a[j + k], t = a[j + s + k] * w % mod;
				b[k] = (u + t) % mod;
				b[n/2 + k] = (u - t + mod) % mod;
			}
			w = w * ws % mod;
		}
		swap(a, b);
	}
	if (inv) {
		ll div = powMod(n, mod - 2, mod);
		for (auto& x : a) x = x * div % mod;
}}
