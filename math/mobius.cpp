ll mu(ll n) { // Laufzeit: O(sqrt(n));
	ll res = 1;
	for (ll i = 2; i * i <= n; i++) {
		if (n % i == 0) {	// Optimierung: Nur Primzahlen
			if (n % (i * i) == 0) return 0;
			res *= -1;
			n /= i;
	}}
	return n > 1 ? -res : res;
}

// berechnet Möbiusfunktion. Laufzeit: O(N*log(log(N)))
vector<int> mu(n + 1, 1);
for (ll i = 2; i <= n; i++) {
	if (mu[i] == 1) {
		for (ll j = i; j <= n; j += i) mu[j] *= -2;
		for (ll j = i*i; j <= n; j += i*i) mu[j] = 0;
	}
	// log2(abs(mu[i])) = number of primes
	mu[i] = (mu[i] > 0) - (mu[i] < 0);
}
