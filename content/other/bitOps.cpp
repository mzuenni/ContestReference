// Iteriert über alle Teilmengen einer Bitmaske
// (außer der leeren Menge).
for (int subset = bitmask; subset > 0;
     subset = (subset - 1) & bitmask)

// Nächste Permutation in Bitmaske
// (z.B. 00111 => 01011 => 01101 => ...)
ll nextPerm(ll v) {
	ll t = v | (v - 1);
	return (t+1) | (((~t & -~t) - 1) >> (__builtin_ctzll(v) + 1));
}
