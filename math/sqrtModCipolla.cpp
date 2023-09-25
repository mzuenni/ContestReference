bool isSquare(ll x, ll p){
    return powMod(x, p/2, p) != p-1;
}

// Teste vorher, ob sqrt(n) mod p existiert!
ll sqrtMod(ll n, ll p){
    if(n == 0) return 0;
    ll r0 = 1, r1 = 0, b0 = 1, b1 = 1, w;
    while(isSquare(w=(b0*b0-n+p)%p, p)) b0 = rng()%p;
    for(ll e = (p+1)/2; e; e /= 2, tie(b0, b1) = pair((b0*b0 + b1*b1%p*w)%p, 2*b0*b1%p))
        if(e & 1) tie(r0, r1) = pair((r0*b0 + r1*b1%p*w)%p, (r0*b1 + b0*r1)%p);
    return r0;
}
