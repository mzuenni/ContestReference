using lll = __int128;

constexpr lll multipliers[] = {1, 3, 5, 7,
                               11, 3*5, 3*7, 3*11,
                               5*7, 5*11, 7*11,
                               3*5*7, 3*5*11, 3*7*11,
                               5*7*11, 3*5*7*11};

lll root(lll x) {
	lll r = sqrtl(x);
	while(r*r < x) r++;
	while(r*r > x) r--;
	return r;
}

lll croot(lll x) {
	lll r = cbrtl(x);
	while(r*r*r < x) r++;
	while(r*r*r > x) r--;
	return r;
}

lll squfof(lll N) {
	lll s = croot(N);
	if (s*s*s == N) return s;
	s = root(N);
	if (s*s == N) return s;
	for (lll k : multipliers) {
		lll D = k * N;
		lll Po, P, Pprev, q, b, r, i;
		Po = Pprev = P = root(D);
		lll Qprev = 1;
		lll Q = D - Po*Po;
		lll L = 2 * root(2 * s);
		lll B = 3 * L;
		for (i = 2; i < B; i++) {
			b = (Po + P) / Q;
			P = b*Q - P;
			q = Q;
			Q = Qprev + b * (Pprev - P);
			r = root(Q);
			if (!(i & 1) && r*r == Q) break;
			Qprev = q;
			Pprev = P;
		}
		if (i >= B) continue;
		b = (Po - P) / r;
		Pprev = P = b*r + P;
		Qprev = r;
		Q = (D-Pprev*Pprev)/Qprev;
		i = 0;
		do {
			b = (Po + P) / Q;
			Pprev = P;
			P = b*Q - P;
			q = Q;
			Q = Qprev +	b * (Pprev - P);
			Qprev = q;
			i++;
		} while(P != Pprev);
		r = gcd(N, Qprev);
		if (r != 1 && r != N) return r;
	}
	exit(1);//try fallback to pollard rho
}

constexpr lll trialLim = 5'000;

void factor(lll n, map<lll, int>& facts) {
	for (lll i = 2; i * i <= n && i <= trialLim; i++) {
		while (n % i == 0) {
			facts[i]++;
			n /= i;
	}}
	if (n > 1 && n < trialLim * trialLim) {
		facts[n]++;
	} else {
		vector<lll> todo = {n};
		while (!todo.empty()) {
			lll c = todo.back();
			todo.pop_back();
			if (c == 1) continue;
			if (isPrime(c)) {
				facts[c]++;
			} else {
				lll d = squfof(c);
				todo.push_back(d);
				todo.push_back(c / d);
}}}}
