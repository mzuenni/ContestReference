constexpr int ALPHABET_SIZE = 26;
constexpr char OFFSET = 'a';
struct SuffixAutomaton {
	struct State {
		int len, link = -1;
		array<int, ALPHABET_SIZE> next = {}; // map if large Alphabet
		State(int l) : len(l) {}
	};

	vector<State> st = {State(0)};
	int cur = 0;

	SuffixAutomaton(const string& s) {
		st.reserve(2 * sz(s));
		for (auto c : s) extend(c - OFFSET);
	}

	void extend(int c) {
		int p = cur;
		cur = sz(st);
		st.emplace_back(st[p].len + 1);
		for (; p != -1 && !st[p].next[c]; p = st[p].link) {
			st[p].next[c] = cur;
		}
		if (p == -1) st[cur].link = 0;
		else {
			int q = st[p].next[c];
			if (st[p].len + 1 == st[q].len) {
				st[cur].link = q;
			} else {
				st.emplace_back(st[p].len + 1);
				st.back().link = st[q].link;
				st.back().next = st[q].next;
				for (; p != -1 && st[p].next[c] == q; p = st[p].link) {
					st[p].next[c] = sz(st) - 1;
				}
				st[q].link = st[cur].link = sz(st) - 1;
	}}}

	vector<int> calculateTerminals() {
		vector<int> terminals;
		for (int p = cur; p != -1; p = st[p].link) {
			terminals.push_back(p);
		}
		return terminals;
	}

	// Pair with start index (in t) and length of LCS.
	pair<int, int> longestCommonSubstring(const string& t) {
		int v = 0, l = 0, best = 0, bestp = -1;
		for (int i = 0; i < sz(t); i++) {
			int c = t[i] - OFFSET;
			while (v && !st[v].next[c]) v = st[v].link, l = st[v].len;
			if (st[v].next[c]) v = st[v].next[c], l++;
			if (l > best) best = l, bestp = i;
		}
		return {bestp - best + 1, best};
	}
};
