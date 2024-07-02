// q = 29, 53, 101, 257, 1009, 65'537
// or choose q random from [sigma, m)
// m = 1'500'000'001, 1'600'000'009, 1'700'000'009
template<ll M, ll Q>
struct Hasher {
	vector<ll> power = {1}, pref = {0};
	Hasher(const string& s) {
		for (auto x : s) {
			power.push_back(power.back() * Q % M);
			pref.push_back((pref.back() * Q % M + x) % M);
	}}

	ll hash(int l, int r) {	// Berechnet hash(s[l..r)).
		return (pref[r] - power[r-l] * pref[l] % M + M) % M;
	}
};
