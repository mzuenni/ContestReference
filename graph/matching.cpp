constexpr int MOD=1'000'000'007, I=10;
vector<vector<ll>> adjlist, mat;

int gauss(int n, ll p) {
	int rank = n;
	for (int line = 0; line < n; line++) {
		int swappee = line;
		while (swappee < n && mat[swappee][line] == 0) swappee++;
		if (swappee == n) {rank--; continue;}
		swap(mat[line], mat[swappee]);
		ll factor = powMod(mat[line][line], p - 2, p);
		for (int i = 0; i < n; i++) {
			mat[line][i] *= factor;
			mat[line][i] %= p;
		}
		for (int i = 0; i < n; i++) {
			if (i == line) continue;
			ll diff = mat[i][line];
			for (int j = 0; j < n; j++) {
				mat[i][j] -= (diff * mat[line][j]) % p;
				mat[i][j] %= p;
				if (mat[i][j] < 0) mat[i][j] += p;
	}}}
	return rank;
}

int max_matching() {
	int ans = 0;
	mat.assign(sz(adjlist), vector<ll>(sz(adjlist)));
	for (int _ = 0; _ < I; _++) {
		for (int i = 0; i < sz(adjlist); i++) {
			mat[i].assign(sz(adjlist), 0);
			for (int j : adjlist[i]) {
				if (j < i) {
					mat[i][j] = rand() % (MOD - 1) + 1;
					mat[j][i] = MOD - mat[i][j];
		}}}
		ans = max(ans, gauss(sz(adjlist), MOD)/2);
	}
	return ans;
}
