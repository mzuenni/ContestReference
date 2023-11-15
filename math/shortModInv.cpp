ll inv(ll a, ll b){ // a^{-1} mod b
    return 1 < a ? b - inv(b % a, a) * b / a : 1;
}