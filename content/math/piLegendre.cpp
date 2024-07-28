constexpr ll cache = 500; // requires O(cache^3)
vector<vector<ll>> memo(cache * cache, vector<ll>(cache));

ll pi(ll n);

ll phi(ll n, ll k) {
	if (n <= 1 || k < 0) return 0;
	if (n <= primes[k]) return n - 1;
	if (n < N && primes[k] * primes[k] > n) return n - pi(n) + k;
	bool ok = n < cache * cache;
	if (ok && memo[n][k] > 0) return memo[n][k];
	ll res = n/primes[k] - phi(n/primes[k], k - 1) + phi(n, k - 1);
	if (ok) memo[n][k] = res;
	return res;
}

ll pi(ll n) {
	if (n < N) { // implement this as O(1) lookup for speedup!
		return distance(primes.begin(), upper_bound(all(primes), n));
	} else {
		ll k = pi(sqrtl(n) + 1);
		return n - phi(n, k) + k;
}}
