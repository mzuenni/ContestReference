constexpr ll N = 10000000;
ll smallest[N], power[N], sieved[N];
vector<ll> primes;

//wird aufgerufen mit (p^k, p, k) für prime p
ll mu(ll pk, ll p, ll k) {return -(k == 1);}
ll phi(ll pk, ll p, ll k) {return pk - pk / p;}
ll div(ll pk, ll p, ll k) {return k+1;}
ll divSum(ll pk, ll p, ll k) {return (pk*p+1) / (p - 1);}
ll square(ll pk, ll p, ll k) {return k % 2 ? pk / p : pk;}
ll squareFree(ll pk, ll p, ll k) {return k % 2 ? pk : 1;}

void sieve() { // O(N)
	smallest[1] = power[1] = sieved[1] = 1;
	for (ll i = 2; i < N; i++) {
		if (smallest[i] == 0) {
			primes.push_back(i);
			for (ll pk = i, k = 1; pk < N; pk *= i, k++) {
				smallest[pk] = i;
				power[pk] = pk;
				sieved[pk] = mu(pk, i, k); // Aufruf ändern!
		}}
		for (ll j = 0; i * primes[j] < N && primes[j] < smallest[i]; j++) {
			ll k = i * primes[j];
			smallest[k] = power[k] = primes[j];
			sieved[k] = sieved[i] * sieved[primes[j]];
		}
		if (i * smallest[i] < N && power[i] != i) {
			ll k = i * smallest[i];
			smallest[k] = smallest[i];
			power[k] = power[i] * smallest[i];
			sieved[k] = sieved[power[k]] * sieved[k / power[k]];
}}}

ll naive(ll n) { // O(sqrt(n))
	ll res = 1;
	for (ll p = 2; p * p <= n; p++) {
		if (n % p == 0) {
			ll pk = 1;
			ll k = 0;
			do {
				n /= p;
				pk *= p;
				k++;
			} while (n % p == 0);
		res *= mu(pk, p, k); // Aufruf ändern!
	}}
	return res;
}
