void normalLine(int line, ll p) {
	ll factor = multInv(mat[line][line], p);
	for (ll& x : mat[line]) x = (x * factor) % p;
}

void takeAll(int n, int line, ll p) {
	for (int i = 0; i < n; i++) {
		if (i == line) continue;
		ll diff = mat[i][line];
		for (int j = 0; j <= n; j++) {
			mat[i][j] -= (diff * mat[line][j]) % p;
			mat[i][j] = (mat[i][j] + p) % p;
}}}

void gauss(int n, ll mod) {
	vector<bool> done(n, false);
	for (int i = 0; i < n; i++) {
		int j = 0;
		while (j < n && (done[j] || mat[j][i] == 0)) j++;
		if (j == n) continue;
		swap(mat[i], mat[j]);
		normalLine(i, mod);
		takeAll(n, i, mod);
		done[i] = true;
}}
// für Eindeutigkeit, Existenz etc. siehe LGS über R
