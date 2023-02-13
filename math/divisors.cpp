ll countDivisors(ll n) {
	ll res = 1;
	for (ll i = 2; i * i * i <= n; i++) {
		ll c = 0;
		while (n % i == 0) {n /= i; c++;}
		res *= c + 1;
	}
	if (isPrime(n)) res *= 2;
	else if (n > 1) res *= isSquare(n) ? 3 : 4;
	return res;
}
