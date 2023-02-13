/*constexpr ll mod = 998244353; @\hl{NTT only}@
constexpr ll root = 3;*/

using cplx = complex<double>;

@\hl{NTT, xor, or, and}@
//void fft(vector<ll> &a, bool inverse = 0) {
void fft(vector<cplx>& a, bool inverse = 0) {
	int n = a.size();
	for (int i = 0, j = 1; j < n - 1; ++j) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	for (int s = 1; s < n; s *= 2) {
		/*ll ws = powMod(root, (mod - 1) / s >> 1, mod); @\hl{NTT only}@
		if (inverse) ws = powMod(ws, mod - 2, mod);*/
		double angle = PI / s * (inverse ? -1 : 1);
		cplx ws(cos(angle), sin(angle));
		for (int j = 0; j < n; j+= 2 * s) {
			//ll w = 1; @\hl{NTT only}@
			cplx w = 1;
			for (int k = 0; k < s; k++) {
				/*ll u = a[j + k], t = a[j + s + k] * w; @\hl{NTT only}@
				t %= mod;
				a[j + k] = (u + t) % mod;
				a[j + s + k] = (u - t + mod) % mod;
				w = (w * ws) % mod;*/
				/*ll u = a[j + k], t = a[j + s + k]; @\hl{xor only}@
				a[j + k] = u + t;
				a[j + s + k] = u - t;*/
				/*if (!inverse) { @\hl{or only}@
					a[j + k] = u + t;
					a[j + s + k] = u;
				} else {
					a[j + k] = t;
					a[j + s + k] = u - t;
				}*/
				/*if (!inverse) { @\hl{and only}@
					a[j + k] = t;
					a[j + s + k] = u + t;
				} else {
					a[j + k] = t - u;
					a[j + s + k] = u;
				}*/
				cplx u = a[j + k], t = a[j + s + k] * w;
				a[j + k] = u + t;
				a[j + s + k] = u - t;
				if (inverse) a[j + k] /= 2, a[j + s + k] /= 2;
				w *= ws;
	}}}
	/*if (inverse) { @\hl{NTT only}@
		ll div = powMod(n, mod - 2, mod);
		for (ll i = 0; i < n; i++) {
			a[i] = (a[i] * div) % mod;
	}}*/
	/*if (inverse) { @\hl{xor only}@
		for (ll i = 0; i < n; i++) {
			a[i] /= n;
	}}*/
}
