// q = 29, 53, 101, 257, 1009, 65'537
// or choose q random from [sigma, m)
// m = 1'500'000'001, 1'600'000'009, 1'700'000'009
struct Hasher {
	vector<ll> power = {1}, pref = {0};
	ll m, q; char c;
	Hasher(const string& s, ll m, ll q, char c) :
	       m(m), q(q), c(c) {
		for (char x : s) {
			power.push_back(power.back() * q % m);
			pref.push_back((pref.back() * q % m + (x - c)) % m);
	}}

	ll hash(int l, int r) {	 // Berechnet hash(s[l..r)).
		return (pref[r] - power[r-l] * pref[l] % m + m) % m;
	}
};
