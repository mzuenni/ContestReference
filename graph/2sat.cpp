struct sat2 {
	int n; // + scc variablen
	vector<int> sol;

	sat2(int vars) : n(vars*2), adjlist(vars*2) {};

	static int var(int i) {return i << 1;}

	void addImpl(int v1, int v2) {
		adjlist[v1].push_back(v2);
		adjlist[1^v2].push_back(1^v1);
	}
	void addEquiv(int v1, int v2) {addImpl(v1, v2); addImpl(v2, v1);}
	void addOr(int v1, int v2) {addImpl(1^v1, v2);}
	void addXor(int v1, int v2) {addOr(v1, v2); addOr(1^v1, 1^v2);}
	void addTrue(int v1) {addImpl(1^v1, v1);}
	void addFalse(int v1) {addTrue(1^v1);}
	void addAnd(int v1, int v2) {addTrue(v1); addTrue(v2);}
	void addNand(int v1, int v2) {addOr(1^v1, 1^v2);}

	bool solvable() {
		scc(); //scc code von oben
		for (int i = 0; i < n; i += 2) {
			if (idx[i] == idx[i + 1]) return false;
		}
		return true;
	}

	void assign() {
		sol.assign(n, -1);
		for (int i = 0; i < sccCounter; i++) {
			if (sol[sccs[i][0]] == -1) {
				for (int v : sccs[i]) {
					sol[v] = 1;
					sol[1^v] = 0;
	}}}}
};
