ll firstVal(ll a, ll m, ll l, ll r) {
	if (l == 0) return 0;
	if (a == 0) return -1;
	if ((l-1)/a < r/a) return (l+a-1) / a*a;
	ll s = (r+a-1) / a*a;
	ll v = firstVal(m % a, a, s-r, s-l);
	return v < 0 ? -1 : s - v;
}

ll minMod(ll n, ll m, ll a, ll b) {
	if (a == 0) return b;
	ll g = gcd(m, a);
	ll c = b % g;
	m /= g;
	a /= g;
	b /= g;
	ll ai = multInv(a, m);
	ll l = ai*b % m;
	ll r = (n-1 + ai*b) % m;
	if (n >= m || l > r) return c;
	return a * firstVal(ai, m, l, r) % m * g + c;
}