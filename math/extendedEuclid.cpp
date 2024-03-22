// a*x + b*y = ggt(a, b)
array<ll, 3> extendedEuclid(ll a, ll b) {
	if (a == 0) return {b, 0, 1};
	auto [d, x, y] = extendedEuclid(b % a, a);
	return {d, y - (b / a) * x, x};
}
