constexpr int ALPHABET_SIZE = 26;
constexpr char OFFSET = 'a';
struct SuffixAutomaton {
	struct State {
		int len, link = -1;
		int nxt[ALPHABET_SIZE] = {}; // map if large Alphabet
		State(int l) : len(l) {}
	};

	vector<State> st{0};
	int last = 0;

	SuffixAutomaton(const string &s) {
		st.reserve(2 * sz(s));
		for (auto c : s) extend(c - OFFSET);
	}

	void extend(int c) {
		st.emplace_back(st[last].len + 1);
		int p = last, cur = last = sz(st) - 1;
		for (; p != -1 && !st[p].nxt[c]; p = st[p].link) {
			st[p].nxt[c] = cur;
		}
		if (p == -1) st[cur].link = 0;
		else {
			int q = st[p].nxt[c];
			if (st[p].len + 1 == st[q].len) {
				st[cur].link = q;
			} else {
				st.emplace_back(st[p].len + 1);
				st.back().link = st[q].link;
				copy(all(st[q].nxt), st.back().nxt); // back.nxt=[q].nxt
				for (; p != -1 && st[p].nxt[c] == q; p = st[p].link) {
					st[p].nxt[c] = sz(st) - 1;
				}
				st[q].link = st[cur].link = sz(st) - 1;
		}}
	}

	vector<int> calculateTerminals() {
		vector<int> terminals;
		for (int p = last; p != -1; p = st[p].link) {
			terminals.push_back(p);
		}
		return terminals;
	}

	// Pair with start index (in t) and length of LCS.
	pair<int, int> longestCommonSubstring(const string &t) {
		int v = 0, l = 0, best = 0, bestpos = 0;
		for (int i = 0; i < sz(t); i++) {
			int c = t[i] - OFFSET;
			for (; v && !st[v].nxt[c]; v = st[v].link) l = st[v].len;
			if (st[v].nxt[c]) v = st[v].nxt[c], l++;
			if (l > best) best = l, bestpos = i;
		}
		return {bestpos - best + 1, best};
	}
};
