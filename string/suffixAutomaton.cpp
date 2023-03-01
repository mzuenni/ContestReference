constexpr char MIN_CHAR = 'a';
constexpr ll ALPHABET_SIZE = 26;
struct SuffixAutomaton {
	struct State {
		int length, link;
		vector<int> next;
		State() : next(ALPHABET_SIZE) {}
	};
	vector<State> states;
	int size, last;

	SuffixAutomaton(const string &s) : states(2*sz(s)) {
		size = 1; last = 0;
		states[0].link = -1;
		for (auto c : s) extend(c - MIN_CHAR);
	}

	void extend(int c) {
		int current = size++;
		states[current].length = states[last].length + 1;
		int pos = last;
		while (pos != -1 && !states[pos].next[c]) {
			states[pos].next[c] = current;
			pos = states[pos].link;
		}
		if (pos == -1) states[current].link = 0;
		else {
			int q = states[pos].next[c];
			if (states[pos].length + 1 == states[q].length) {
				states[current].link = q;
			} else {
				int clone = size++;
				states[clone].length = states[pos].length + 1;
				states[clone].link = states[q].link;
				states[clone].next = states[q].next;
				while (pos != -1 && states[pos].next[c] == q) {
					states[pos].next[c] = clone;
					pos = states[pos].link;
				}
				states[q].link = states[current].link = clone;
		}}
		last = current;
	}

	// Pair with start index (in t) and length of LCS.
	pair<int, int> longestCommonSubstring(const string &t) {
		int v = 0, l = 0, best = 0, bestpos = 0;
		for (int i = 0; i < sz(t); i++) {
			int c = t[i] - MIN_CHAR;
			while (v && !states[v].next[c]) {
				v = states[v].link;
				l = states[v].length;
			}
			if (states[v].next[c]) {v = states[v].next[c]; l++;}
			if (l > best) {best = l; bestpos = i;}
		}
		return {bestpos - best + 1, best};
	}

	// Returns all terminals of the automaton.
	vector<int> calculateTerminals() {
		vector<int> terminals;
		int pos = last;
		while (pos != -1) {
			terminals.push_back(pos);
			pos = states[pos].link;
		}
		return terminals;
	}
};
