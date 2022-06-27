// Q = Anzahl der Anfragen
// C = Anzahl der Schritte der Operation

vector<vector<int>> focus;
vector<int> low, high, ans;

ans.assign(Q, C + 1);
low.assign(Q, 0);
high.assign(Q, C);
focus.assign(C + 1, vector<int>());
for (bool changed = true; changed;) {
	changed = false;
	for (int i = 0; i <= C; i++) focus[i].clear();
	for (int i = 0; i < Q; i++) {
		if (low[i] > high[i]) continue;
		focus[(low[i] + high[i]) / 2].pb(i);
	}

	// Simulation zurücksetzen

	for (int k = 0; k <= C; k++) {
		// Simulationsschritt

		for (int q : focus[k]) {
			changed = true;
			if (/* Eigenschaft schon erfüllt */) {
				// Antwort updaten
				high[q] = k - 1;
				ans[q] = min(ans[q], k);
			} else {
				low[q] = k + 1;
}}}}
