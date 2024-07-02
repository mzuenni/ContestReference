// M = 1.7e9 + 9, 1e18L + 9, 2.2e18L + 7
struct Hash {
	static constexpr ll M = 3e18L + 37;
	static constexpr ll Q = 318LL << 53; // Random in [SIGMA+1, M)
	vector<ll> pref = {0}, power = {1};

	Hash(const string& s) {
		for (auto c : s) {
			pref.push_back((mul(pref.back(), Q) + c + M) % M);
			power.push_back(mul(power.back(), Q));
	}}

	ll operator()(int l, int r) {
		return (pref[r] - mul(power[r-l], pref[l]) + M) % M;
	}

	static ll mul(__int128 a, ll b) {return a * b % M;}
};
