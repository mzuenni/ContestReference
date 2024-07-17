void normalLine(int line) {
	double factor = mat[line][line];
	for (double& x : mat[line]) x /= factor;
}

void takeAll(int n, int line) {
	for (int i = 0; i < n; i++) {
		if (i == line) continue;
		double diff = mat[i][line];
		for (int j = 0; j < sz(mat[i]); j++) {
			mat[i][j] -= diff * mat[line][j];
}}}

int gauss(int n) {
	vector<bool> done(n, false);
	for (int i = 0; i < n; i++) {
		int swappee = i; // Sucht Pivotzeile für bessere Stabilität.
		for (int j = 0; j < n; j++) {
			if (done[j]) continue;
			if (abs(mat[j][i]) > abs(mat[i][i])) swappee = j;
		}
		swap(mat[i], mat[swappee]);
		if (abs(mat[i][i]) > EPS) {
			normalLine(i);
			takeAll(n, i);
			done[i] = true;	
	}}
	// Ab jetzt nur checks bzgl. Eindeutigkeit/Existenz der Lösung.
	for (int i = 0; i < n; i++) {
		bool allZero = true;
		for (int j = i; j < n; j++) allZero &= abs(mat[i][j]) <= EPS;
		if (allZero && abs(mat[i][n]) > EPS) return INCONSISTENT;
		if (allZero && abs(mat[i][n]) <= EPS) return MULTIPLE;
	}
	return UNIQUE;
}
