struct SuffixTree {
	struct Vert {
		int start, end, suffix;
		map<char, int> next;
	};
	string s;
	int root, lastIdx, needsSuffix, pos, remainder;
	int curVert, curEdge, curLen;
	// Each Vertex gives its children range as [start, end)
	vector<Vert> tree;

	SuffixTree(string& s) : s(s) {
		needsSuffix = remainder = curEdge = curLen = 0;
		lastIdx = pos = -1;
		root = curVert = newVert(-1, -1);
		for (int i = 0; i < sz(s); i++) extend();
	}

	int newVert(int start, int end) {
		Vert v;
		v.start = start;
		v.end = end;
		v.suffix = 0;
		tree.push_back(v);
		return ++lastIdx;
	}

	int len(Vert& v) {
		return min(v.end, pos + 1) - v.start;
	}

	void addSuffixLink(int vert) {
		if (needsSuffix) tree[needsSuffix].suffix = vert;
		needsSuffix = vert;
	}

	bool fullImplicitEdge(int vert) {
		if (curLen >= len(tree[vert])) {
			curEdge += len(tree[vert]);
			curLen -= len(tree[vert]);
			curVert = vert;
			return true;
		}
		return false;
	}

	void extend() {
		pos++;
		needsSuffix = 0;
		remainder++;
		while (remainder) {
			if (curLen == 0) curEdge = pos;
			if (!tree[curVert].next.count(s[curEdge])) {
				int leaf = newVert(pos, sz(s));
				tree[curVert].next[s[curEdge]] = leaf;
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
			if (curVert == root && curLen) {
				curLen--;
				curEdge = pos - remainder + 1;
			} else {
				curVert = tree[curVert].suffix ? tree[curVert].suffix 
																			 : root;
	}}}
};