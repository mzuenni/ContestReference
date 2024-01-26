constexpr ll bases32[] = {2, 7, 61};
constexpr ll bases64[] = {2, 325, 9375, 28178, 450775,
                          9780504, 1795265022};
bool isPrime(ll n) {
	if (n < 2 || n % 2 == 0) return n == 2;
	ll d = n - 1, j = 0;
	while (d % 2 == 0) d /= 2, j++;
	for (ll a : bases64) {
		if (a % n == 0) continue;
		ll v = powMod(a, d, n); //with mulmod or int128
		if (v == 1 || v == n - 1) continue;
		for (ll i = 1; i <= j; i++) {
			v = ((lll)v * v) % n;
			if (v == n - 1 || v <= 1) break;
		}
		if (v != n - 1) return false;
	}
	return true;
}
