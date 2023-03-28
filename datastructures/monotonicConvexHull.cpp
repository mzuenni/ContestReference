// Lower Envelope mit MONOTONEN Inserts und Queries. Jede neue
// Gerade hat kleinere Steigung als alle vorherigen.
vector<ll> ms, bs;
int ptr = 0;

bool bad(int l1, int l2, int l3) {
	return (bs[l3]-bs[l1])*(ms[l1]-ms[l2]) <
	       (bs[l2]-bs[l1])*(ms[l1]-ms[l3]);
}

void add(ll m, ll b) { // Laufzeit O(1) amortisiert
	ms.push_back(m); bs.push_back(b);
	while (sz(ms) >= 3 && bad(sz(ms)-3, sz(ms)-2, sz(ms)-1)) {
		ms.erase(ms.end() - 2); bs.erase(bs.end() - 2);
	}
	ptr = min(ptr, sz(ms) - 1);
}

ll get(int idx, ll x) {return ms[idx] * x + bs[idx];}

ll query(ll x) { // Laufzeit: O(1) amortisiert
	if (ptr >= sz(ms)) ptr = sz(ms) - 1;
	while (ptr < sz(ms)-1 && get(ptr + 1, x) < get(ptr, x)) ptr++;
	return get(ptr, x);
}
