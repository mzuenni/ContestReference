struct sat2 {
	int n; // + scc variablen
	vector<int> sol;

	sat2(int vars) : n(vars*2), adj(n) {}

	static int var(int i) {return i << 1;} // use this!

	void addImpl(int a, int b) {
		adj[a].push_back(b);
		adj[1^b].push_back(1^a);
	}
	void addEquiv(int a, int b) {addImpl(a, b); addImpl(b, a);}
	void addOr(int a, int b) {addImpl(1^a, b);}
	void addXor(int a, int b) {addOr(a, b); addOr(1^a, 1^b);}
	void addTrue(int a) {addImpl(1^a, a);}
	void addFalse(int a) {addTrue(1^a);}
	void addAnd(int a, int b) {addTrue(a); addTrue(b);}
	void addNand(int a, int b) {addOr(1^a, 1^b);}

	bool solve() {
		scc(); //scc code von oben
		sol.assign(n, -1);
		for (int i = 0; i < n; i += 2) {
			if (idx[i] == idx[i + 1]) return false;
			sol[i] = idx[i] < idx[i + 1];
			sol[i + 1] = !sol[i];
		}
		return true;
	}
};
