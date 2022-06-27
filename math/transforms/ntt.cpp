constexpr ll mod = 998244353;
constexpr ll root = 3;

void fft(vector<ll>& a, bool inverse = 0) {
	int n = sz(a);
	for (int i = 0, j = 1; j < n - 1; ++j) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	for (int s = 1; s < n; s *= 2) {
		ll ws = powMod(root, (mod - 1) / s >> 1, mod);
		if (inverse) ws = powMod(ws, mod - 2, mod);
		for (int j = 0; j < n; j+= 2 * s) {
			ll w = 1;
			for (int k = 0; k < s; k++) {
				ll u = a[j + k], t = a[j + s + k] * w;
				t %= mod;
				a[j + k] = (u + t) % mod;
				a[j + s + k] = (u - t + mod) % mod;
				w *= ws;
				w %= mod;
	}}}
	if (inverse) {
		ll div = powMod(n, mod - 2, mod);
		for (ll i = 0; i < n; i++) {
			a[i] *= div;
			a[i] %= mod;
}}}
