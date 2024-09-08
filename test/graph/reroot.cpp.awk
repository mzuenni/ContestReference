BEGIN { print "constexpr ll MOD = 1e9 + 7;" }
{ 
    sub("W w, T x) {\\}", "W w, T x) { return ((v ^ c) + x) * w % MOD; }")
    sub("T x, T y) {\\}", "T x, T y) { return x ^ y; }")
    sub("int v, T x) {\\}", "int v, T x) { return v ^ x; }")
}
{ print }
