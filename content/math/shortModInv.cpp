ll multInv(ll x, ll m) { // x^{-1} mod m
    return 1 < x ? m - inv(m % x, x) * m / x : 1;
}
