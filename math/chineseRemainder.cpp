struct CRT{
	using lll = __int128_t;
  lll M = 1, sol = 0; // Solution unique modulo M
  bool hasSol = true;

  // Adds congruence x = a (mod m)
  void add(ll a, ll m){
    ll s, t, d = extendedEuclid(M, m, s, t);
    if((a - sol) % d != 0) hasSol = false;
    lll z = M/d * s;
    M *= m/d;
    sol = (z % M * (a-sol) % M + sol + M) % M;
  }
};