ll divSum(ll n, ll m, ll a, ll b){
	if (m == 0) return 0;
	ll ans = a/m * n*(n-1)/2 + b/m * n;
	a %= m;
	b %= m;
	ll y = (a*(n-1)+b) / m;
	return ans + y * (n-1) - divSum(y, a, m, m-b-1);
}
