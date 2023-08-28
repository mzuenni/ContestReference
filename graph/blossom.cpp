struct GM {
	vector<vector<int>> adj;
	// pairs ist der gematchte knoten oder n
	vector<int> pairs, first, que;
	vector<pair<int, int>> label;
	int head, tail;

	GM(int n) : adj(n), pairs(n + 1, n), first(n + 1, n),
	            que(n), label(n + 1, {-1, -1}) {}

	void rematch(int u, int v) {
		int t = pairs[u]; pairs[u] = v;
		if (pairs[t] != u) return;
		if (label[u].second == -1) {
			pairs[t] = label[u].first;
			rematch(pairs[t], t);
		} else {
			auto [x, y] = label[u];
			rematch(x, y);
			rematch(y, x);
	}}

	int findFirst(int v) {
		return label[first[v]].first < 0 ? first[v]
		     : first[v] = findFirst(first[v]);
	}

	void relabel(int x, int y) {
		int r = findFirst(x);
		int s = findFirst(y);
		if (r == s) return;
		auto h = label[r] = label[s] = {~x, y};
		int join;
		while (true) {
			if (s != sz(adj)) swap(r, s);
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

	bool augment(int v) {
		label[v] = {sz(adj), -1};
		first[v] = sz(adj);
		head = tail = 0;
		for (que[tail++] = v; head < tail;) {
			int x = que[head++];
			for (int y : adj[x]) {
				if (pairs[y] == sz(adj) && y != v) {
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
		for (int v = 0; v < sz(adj); v++) {
			if (pairs[v] < sz(adj) || !augment(v)) continue;
			matching++;
			for (int i = 0; i < tail; i++)
				label[que[i]] = label[pairs[que[i]]] = {-1, -1};
			label[sz(adj)] = {-1, -1};
		}
		return matching;
	}
};
