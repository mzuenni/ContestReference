/*constexpr ll mod = 998244353; @\hl{NTT only}@
constexpr ll root = 3;*/

using cplx = complex<double>;

//void fft(vector<ll> &a, bool inverse = 0) { @\hl{NTT, xor, or, and}@
void fft(vector<cplx>& a, bool inverse = 0) {
	int n = sz(a);
	for (int i = 0, j = 1; j < n - 1; ++j) {
		for (int k = n >> 1; k > (i ^= k); k >>= 1);
		if (j < i) swap(a[i], a[j]);
	}
	static vector<cplx> ws(2, 1);
	for (static int k = 2; k < n; k *= 2) {
		ws.resize(n);
		cplx w = polar(1.0, acos(-1.0) / k);
		for (int i=k; i<2*k; i++) ws[i] = ws[i/2] * (i % 2 ? w : 1);
	}
	for (int s = 1; s < n; s *= 2) {
		/*ll ws = powMod(root, (mod - 1) / s >> 1, mod); @\hl{NTT only}@
		if (inverse) ws = powMod(ws, mod - 2, mod);*/
		for (int j = 0; j < n; j += 2 * s) {
			//ll w = 1; @\hl{NTT only}@
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
				cplx u = a[j + k], t = a[j + s + k];
				t *= (inverse ? conj(ws[s + k]) : ws[s + k]);
				a[j + k] = u + t;
				a[j + s + k] = u - t;
				if (inverse) a[j + k] /= 2, a[j + s + k] /= 2;
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
