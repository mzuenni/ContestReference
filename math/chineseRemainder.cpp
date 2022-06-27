// Laufzeit: O(n * log(n)), n := Anzahl der Kongruenzen
// Nur für teilerfremde Moduli. Berechnet das kleinste, 
// nicht negative x, das alle Kongruenzen simultan löst. 
// Alle Lösungen sind kongruent zum kgV der Moduli
// (Produkt, falls alle teilerfremd sind).
struct ChineseRemainder {
	using lll = __int128;
	vector<lll> lhs, rhs, mods, inv;
	lll M; // Produkt über die Moduli. Kann leicht überlaufen.

	ll g(vector<lll> &vec) {
		lll res = 0;
		for (int i = 0; i < sz(vec); i++) {
			res += (vec[i] * inv[i]) % M;
			res %= M;
		}
		return res;
	}

	// Fügt Kongruenz l * x = r (mod m) hinzu.
	void addEquation(ll l, ll r, ll m) {
		lhs.push_back(l);
		rhs.push_back(r);
		mods.push_back(m);
	}

	// Löst das System.
	ll solve() {
		M = accumulate(mods.begin(), mods.end(), lll(1), 
									 multiplies<lll>());
		inv.resize(sz(lhs));
		for (int i = 0; i < sz(lhs); i++) {
			lll x = (M / mods[i]) % mods[i];
			inv[i] = (multInv(x, mods[i]) * (M / mods[i]));
		}
		return (multInv(g(lhs), M) * g(rhs)) % M;
	}
};
