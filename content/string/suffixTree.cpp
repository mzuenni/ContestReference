struct SuffixTree {
	struct Vert {
		int start, end, suf;
		map<char, int> next;
	};
	string s;
	int needsSuffix, pos, remainder, curVert, curEdge, curLen;
	// Each Vertex gives its children range as [start, end)
	vector<Vert> tree = {Vert{-1, -1, 0, {}}};

	SuffixTree(const string& s) : s(s) {
		needsSuffix = remainder = curVert = curEdge = curLen = 0;
		pos = -1;
		for (int i = 0; i < sz(s); i++) extend();
	}

	int newVert(int start, int end) {
		tree.push_back({start, end, 0, {}});
		return sz(tree) - 1;
	}

	void addSuffixLink(int vert) {
		if (needsSuffix) tree[needsSuffix].suf = vert;
		needsSuffix = vert;
	}

	bool fullImplicitEdge(int vert) {
		int len = min(tree[vert].end, pos + 1) - tree[vert].start;
		if (curLen >= len) {
			curEdge += len;
			curLen -= len;
			curVert = vert;
			return true;
		} else {
			return false;
	}}

	void extend() {
		pos++;
		needsSuffix = 0;
		remainder++;
		while (remainder) {
			if (curLen == 0) curEdge = pos;
			if (!tree[curVert].next.count(s[curEdge])) {
				int leaf = newVert(pos, sz(s));
				tree[curVert].next[s[curEdge]] = leaf;
				addSuffixLink(curVert);
			} else {
				int nxt = tree[curVert].next[s[curEdge]];
				if (fullImplicitEdge(nxt)) continue;
				if (s[tree[nxt].start + curLen] == s[pos]) {
					curLen++;
					addSuffixLink(curVert);
					break;
				}
				int split = newVert(tree[nxt].start,
				                    tree[nxt].start + curLen);
				tree[curVert].next[s[curEdge]] = split;
				int leaf = newVert(pos, sz(s));
				tree[split].next[s[pos]] = leaf;
				tree[nxt].start += curLen;
				tree[split].next[s[tree[nxt].start]] = nxt;
				addSuffixLink(split);
			}
			remainder--;
			if (curVert == 0 && curLen) {
				curLen--;
				curEdge = pos - remainder + 1;
			} else {
				curVert = tree[curVert].suf ? tree[curVert].suf : 0;
	}}}
};