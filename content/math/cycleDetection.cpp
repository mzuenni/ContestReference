pair<ll, ll> cycleDetection(ll x0, function<ll(ll)> f) {
	ll a = x0, b = f(x0), length = 1;
	for (ll power = 1; a != b; b = f(b), length++) {
		if (power == length) {
			power *= 2;
			length = 0;
			a = b;
	}}
	ll start = 0;
	a = x0; b = x0;
	for (ll i = 0; i < length; i++) b = f(b);
	while (a != b) {
		a = f(a);
		b = f(b);
		start++;
	}
	return {start, length};
}
