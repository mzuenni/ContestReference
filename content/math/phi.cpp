ll phi(ll n) { // Laufzeit: O(sqrt(n))
	// Optimierung: Falls n prim, n - 1 zurückgeben
	ll result = n;
	for(ll i = 2; i * i <= n; ++i) {
		if(n % i == 0) {	// Optimierung: Nur Primzahlen
			while(n % i == 0) n /= i;
			result -= result / i;
	}}
	if(n > 1) result -= result / n;
	return result;
}

// Sieb, falls alle Werte benötigt werden.
// Laufzeit: O(N*log(log(N)))
vector<ll> phi(n + 1);
for (int i = 1; i <= n; i++) phi[i] = i;
for (int i = 2; i <= n; i++) if (phi[i] == i) {
	for (int j = i; j <= n; j += i) {
		phi[j] /= i;
		phi[j] *= i - 1;
}}
