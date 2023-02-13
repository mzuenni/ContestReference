struct GM {
	vector<vector<int>> adjlist;
	// pairs ist der gematchte knoten oder n
	vector<int> pairs, first, que;
	vector<pair<int, int>> label;
	int head, tail;

	GM(int n) : adjlist(n), pairs(n + 1, n), first(n + 1, n), 
	            que(n), label(n + 1, {-1, -1}) {}

	void rematch(int v, int w) {
		int t = pairs[v]; pairs[v] = w;
		if (pairs[t] != v) return;
		if (label[v].second == -1) {
			pairs[t] = label[v].first;
			rematch(pairs[t], t);
		} else {
			int x = label[v].first;
			int y = label[v].second;
			rematch(x, y);
			rematch(y, x);
	}}

	int findFirst(int u) {
		return label[first[u]].first < 0 ? first[u]
		     : first[u] = findFirst(first[u]);
	}

	void relabel(int x, int y) {
		int r = findFirst(x);
		int s = findFirst(y);
		if (r == s) return;
		auto h = label[r] = label[s] = {~x, y};
		int join;
		while (true) {
			if (s != sz(adjlist)) swap(r, s);
			r = findFirst(label[pairs[r]].first);
			if (label[r] == h) {
				join = r;
				break;
			} else {
				label[r] = h;
		}}
		for (int v : {first[x], first[y]}) {
			for (; v != join; v = first[label[pairs[v]].first]) {
				label[v] = {x, y};
				first[v] = join;
				que[tail++] = v;
	}}}

	bool augment(int u) {
		label[u] = {sz(adjlist), -1};
		first[u] = sz(adjlist);
		head = tail = 0;
		for (que[tail++] = u; head < tail;) {
			int x = que[head++];
			for (int y : adjlist[x]) {
				if (pairs[y] == sz(adjlist) && y != u) {
					pairs[y] = x;
					rematch(x, y);
					return true;
				} else if (label[y].first >= 0) {
					relabel(x, y);
				} else if (label[pairs[y]].first == -1) {
					label[pairs[y]].first = x;
					first[pairs[y]] = y;
					que[tail++] = pairs[y];
		}}}
		return false;
	}

	int match() {
		int matching = head = tail = 0;
		for (int u = 0; u < sz(adjlist); u++) {
			if (pairs[u] < sz(adjlist) || !augment(u)) continue;
			matching++;
			for (int i = 0; i < tail; i++)
				label[que[i]] = label[pairs[que[i]]] = {-1, -1};
			label[sz(adjlist)] = {-1, -1};
		}
		return matching;
	}
};
