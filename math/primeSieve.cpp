constexpr ll N = 100000000;
bitset<N / 2> isNotPrime;
vector<ll> primes = {2};

bool isPrime(ll x) {
	if (x < 2 || x % 2 == 0) return x == 2;
	else return !isNotPrime[x / 2];
}

void primeSieve() {
	// i * i < N is enough for isPrime
	for (ll i = 3; i < N; i += 2) {
		if (!isNotPrime[i / 2]) {
			primes.push_back(i);
			for (ll j = i * i; j < N; j+= 2 * i) {
				isNotPrime[j / 2] = 1;
}}}}
