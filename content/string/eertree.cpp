constexpr int ALPHABET_SIZE = 26;
constexpr char OFFSET = 'a';
struct Eertree {
	struct State {
		int len, link = 0, par;
		array<int, ALPHABET_SIZE> nxt;

		State(int l, int p) : len(l), par(p) {nxt.fill(-1);}
	};

	vector<State> st = {State(-1, -1), State(0, -1)};
	vector<int> s = {-1};
	int cur = 0;
	Eertree(string& t) {
		st.reserve(sz(t) + 2);
		for (auto c : t) extend(c - OFFSET);
	};

	int getLink(int u) {
		while (s.end()[-st[u].len - 2] != s.back()) u = st[u].link;
		return u;
	}

	void extend(int c) {
		s.push_back(c);
		int old = cur = getLink(cur);
		if (st[cur].nxt[c] == -1) {
			st[cur].nxt[c] = sz(st);
			st.emplace_back(st[cur].len + 2, cur);

			cur = getLink(st[cur].link);
			st.back().link = min(cur + 1, old) ? st[cur].nxt[c] : 1;
		}
		cur = st[old].nxt[c];
	}
};
