// Lower Envelope mit MONOTONEN Inserts und Queries. Jede neue
// Gerade hat kleinere Steigung als alle vorherigen.
struct Line {
	ll m, b;
	ll operator()(ll x) {return m*x+b;}
};

vector<Line> ls;
int ptr = 0;

bool bad(Line l1, Line l2, Line l3) {
	return (l3.b-l1.b)*(l1.m-l2.m) < (l2.b-l1.b)*(l1.m-l3.m);
}

void add(ll m, ll b) { // Laufzeit O(1) amortisiert
	while (sz(ls) > 1 && bad(ls.end()[-2], ls.end()[-1], {m, b})) {
		ls.pop_back();
	}
	ls.push_back({m, b});
	ptr = min(ptr, sz(ls) - 1);
}

ll query(ll x) { // Laufzeit: O(1) amortisiert
	ptr = min(ptr, sz(ls) - 1);
	while (ptr < sz(ls)-1 && ls[ptr + 1](x) < ls[ptr](x)) ptr++;
	return ls[ptr](x);
}