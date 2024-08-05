// Lower Envelope mit MONOTONEN Inserts UND Queries. Jede neue
// Gerade hat kleinere Steigung als alle vorherigen.
struct Line {
	ll m, c;
	ll operator()(ll x) {return m*x+c;}
};

vector<Line> ls;
ll ptr = 0;

bool bad(Line l1, Line l2, Line l3) {
	return (l3.c-l1.c)*(l1.m-l2.m) < (l2.c-l1.c)*(l1.m-l3.m);
}

void add(ll m, ll c) { // Laufzeit O(1) amortisiert
	while (sz(ls) > 1 && bad(ls.end()[-2], ls.end()[-1], {m, c})) {
		ls.pop_back();
	}
	ls.push_back({m, c});
	ptr = min(ptr, sz(ls) - 1);
}

ll query(ll x) { // Laufzeit: O(1) amortisiert
	ptr = min(ptr, sz(ls) - 1);
	while (ptr + 1 < sz(ls) && ls[ptr + 1](x) < ls[ptr](x)) ptr++;
	return ls[ptr](x);
}