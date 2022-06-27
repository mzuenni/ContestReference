void normalLine(int n, int line) {
	double factor = mat[line][line];
	for (int i = 0; i <= n; i++) {
		mat[line][i] /= factor;
}}

void takeAll(int n, int line) {
	for (int i = 0; i < n; i++) {
		if (i == line) continue;
		double diff = mat[i][line];
		for (int j = 0; j <= n; j++) {
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
		if (abs(mat[i][i]) > EPSILON) {
			normalLine(n, i);
			takeAll(n, i);
			done[i] = true;	
	}}
	// Ab jetzt nur checks bzgl. Eindeutigkeit/Existenz der Lösung.
	for (int i = 0; i < n; i++) {
		bool allZero = true;
		for (int j = i; j < n; j++)
			if (abs(mat[i][j]) > EPSILON) allZero = false;
		if (allZero && abs(mat[i][n]) > EPSILON) return INCONSISTENT;
		if (allZero && abs(mat[i][n]) < EPSILON) return MULTIPLE;
	}
	return UNIQUE;
}
