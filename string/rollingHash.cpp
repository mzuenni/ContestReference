// q = 29, 101, 257, 65537, 100003, 1000033 (or random)
// m = 1500000001, 1600000009, 1700000009
// always compare hash and length of hashed range!
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