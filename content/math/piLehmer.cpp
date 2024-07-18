constexpr ll cacheA = 2 * 3 * 5 * 7 * 11 * 13 * 17;
constexpr ll cacheB = 7;
ll memoA[cacheA + 1][cacheB + 1];
ll memoB[cacheB + 1];
ll memoC[N];

void init() {
	primeSieve(); // @\sourceref{math/primeSieve.cpp}@
	for (ll i = 0; i < N; i++) {
		memoC[i] = memoC[i - 1];
		if (isPrime(i)) memoC[i]++;
	}
	memoB[0] = 1;
	for(ll i = 0; i <= cacheA; i++) memoA[i][0] = i;
	for(ll i = 1; i <= cacheB; i++) {
		memoB[i] = primes[i - 1] * memoB[i - 1];
		for(ll j = 1; j <= cacheA; j++) {
			memoA[j][i] = memoA[j][i - 1] - memoA[j /
			              primes[i - 1]][i - 1];
}}}

ll phi(ll n, ll k) {
	if(k == 0) return n;
	if(k <= cacheB) 
		return memoA[n % memoB[k]][k] + 
					 (n / memoB[k]) * memoA[memoB[k]][k];
	if(n <= primes[k - 1]*primes[k - 1]) return memoC[n] - k + 1;
	if(n <= primes[k - 1]*primes[k - 1]*primes[k - 1] && n < N) {
		ll b = memoC[(ll)sqrtl(n)];
		ll res = memoC[n] - (b + k - 2) * (b - k + 1) / 2;
		for(ll i = k; i < b; i++) res += memoC[n / primes[i]];
		return res;
	}
	return phi(n, k - 1) - phi(n / primes[k - 1], k - 1);
}

ll pi(ll n) {
	if (n < N) return memoC[n];
	ll a = pi(sqrtl(sqrtl(n)));
	ll b = pi(sqrtl(n));
	ll c = pi(cbrtl(n));
	ll res = phi(n, a) + (b + a - 2) * (b - a + 1) / 2;
	for (ll i = a; i < b; i++) {
		ll w = n / primes[i];
		res -= pi(w);
		if (i > c) continue;
		ll bi = pi(sqrtl(w));
		for (ll j = i; j < bi; j++) {
			res -= pi(w / primes[j]) - j;
	}}
	return res;
}
