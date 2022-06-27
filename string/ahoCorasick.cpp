constexpr ll ALPHABET_SIZE = 26;
constexpr char OFFSET = 26;
struct AhoCorasick {
	struct vert {
		int suffix, exit, character, parent;
		vector<int> nxt, patterns;
		vert(int c, int p) : suffix(-1), exit(-1), 
				 character(c), nxt(ALPHABET_SIZE, -1), parent(p) {}
	};
	vector<vert> aho;

	AhoCorasick() {aho.push_back(vert(-1, 0));}

	// Call once for each pattern.
	void addString(string &s, int patternIdx) {
		int v = 0;
		for (char c : s) {
			int idx = c - OFFSET;
			if (aho[v].nxt[idx] == -1) {
				aho[v].nxt[idx] = sz(aho);
				aho.emplace_back(idx, v);
			}
			v = aho[v].nxt[idx];
		}
		aho[v].patterns.push_back(patternIdx);
	}

	int getSuffix(int v) {
		if (aho[v].suffix == -1) {
			if (v == 0 || aho[v].parent == 0) aho[v].suffix = 0;
			else aho[v].suffix = go(getSuffix(aho[v].parent), 
															aho[v].character);
		}
		return aho[v].suffix;
	}

	int getExit(int v) {
		if (aho[v].exit == -1) {
			int suffix = getSuffix(v);
			if (v == 0) aho[v].exit = 0;
			else {
				if (aho[suffix].patterns.empty()) {
					aho[v].exit = getExit(suffix);
				} else {
					aho[v].exit = suffix;
		}}}
		return aho[v].exit;
	}

	int go(int v, int idx) { // Root is v=0.
		if (aho[v].nxt[idx] != -1) return aho[v].nxt[idx];
		else return v == 0 ? 0 : go(getSuffix(v), idx);
	}
};