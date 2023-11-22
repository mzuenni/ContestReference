// M = 1.7e9 + 9, 1e18L + 9, 2.2e18L + 7
struct Hash {
    static constexpr ll M = 3.1e18L + 7;
    static constexpr ll Q = 2e18L + 43; // Random number in [SIGMA+1, M)
    vector<ll> pref = {0}, power = {1};

    Hash(const string& s) {
        for (auto c : s) {
            pref.push_back((mul(pref.back(), Q) + c) % M);
            power.push_back(mul(power.back(), Q));
    }}

    ll operator()(int l, int r) {
        return (pref[r] - mul(power[r-l], pref[l]) + M) % M;
    }

    // can also just use __int128 multiplication and mod (slower)
    using ull = uint64_t;
    static ll mul(ull a, ull b) { // 0 < a,b <= M <= 7.268 * 10^18
        ll ans = (a * b - M * ull(1.L / M * a * b));
        return ans + M * ((ans < 0) - (ans >= M));
    }
};
