string a, b; //a needs to be set
vector<int> longest;

//transformes "aa" to ".a.a." to find even length palindromes
void init() {
	b = string(sz(a) * 2 + 1, '.');
	longest.assign(sz(b), 0);
	for (int i = 0; i < sz(a); i++) {
		b[2 * i + 1] = a[i];
}}

void manacher() {
	int center = 0, last = 0, n = sz(b);
	for (int i = 1; i < n - 1; i++) {
		int i2 = 2 * center - i;
		longest[i] = (last > i) ? min(last - i, longest[i2]) : 0;
		while (i + longest[i] + 1 < n && i - longest[i] - 1 >= 0 &&
		       b[i + longest[i] + 1] == b[i - longest[i] - 1]) {
			longest[i]++;
		}
		if (i + longest[i] > last) {
			center = i;
			last = i + longest[i];
	}}
	//convert lengths to string b (optional)
	for (int i = 0; i < n; i++) longest[i] = 2 * longest[i] + 1;
}