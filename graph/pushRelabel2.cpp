constexpr ll inf = 1ll<<60;

struct edge {
	int from, to; 
	ll f, c;
};

vector<edge> edges;
vector<vector<int>> adjlist, llist;
vector<int> height, ccount, que;
vector<ll> excess;
vector<list<int>> dlist;
vector<list<int>::iterator> iter;
int highest, highestActive;

void addEdge(int from, int to, ll c) {
	adjlist[from].push_back(sz(edges));
	edges.push_back({from, to, 0, c});
	adjlist[to].push_back(sz(edges));
	edges.push_back({to, from, 0, 0});
}

void globalRelabel(int n, int t) {
	height.assign(n, n);
	height[t] = 0;
	ccount.assign(n, 0);
	que.assign(n+1, 0);
	int qh = 0, qt = 0;
	for (que[qt++] = t; qh < qt;) {
		int u = que[qh++], h = height[u] + 1;
		for (int id : adjlist[u]) {
			if (height[edges[id].to] == n && edges[id ^ 1].c - edges[id ^ 1].f > 0) {
				ccount[height[edges[id].to] = h]++;
				que[qt++] = edges[id].to;
	}}}
	llist.assign(n+1, {});
	dlist.assign(n+1, {});
	for (int u = 0; u < n; u++) {
		if (height[u] < n) {
			iter[u] = dlist[height[u]].insert(dlist[height[u]].begin(), u);
			if (excess[u] > 0) llist[height[u]].push_back(u);
	}}
	highest = highestActive = height[que[qt - 1]];
}

void push(int u, int id) {
	int v = edges[id].to;
	ll df = min(excess[u], edges[id].c - edges[id].f);
	edges[id].f += df;
	edges[id^1].f -= df;
	excess[u] -= df;
	excess[v] += df;
	if (0 < excess[v] && excess[v] <= df) llist[height[v]].push_back(v);
}

void discharge(int n, int u) {
	int nh = n;
	for (int id : adjlist[u]) {
		if (edges[id].c - edges[id].f > 0) {
			if (height[u] == height[edges[id].to] + 1) {
				push(u, id);
				if (!excess[u]) return;
			} else {
				nh = min(nh, height[edges[id].to] + 1);
	}}}
	int h = height[u];
	if (ccount[h] == 1) {
		for (int i = h; i <= highest; i++) {
			for (auto p : dlist[i]) --ccount[height[p]], height[p] = n;
			dlist[i].clear();
		}
		highest = h - 1;
	} else {
		--ccount[h], iter[u] = dlist[h].erase(iter[u]), height[u] = nh;
		if (nh == n) return;
		++ccount[nh], iter[u] = dlist[nh].insert(dlist[nh].begin(), u);
		highest = max(highest, highestActive = nh);
		llist[nh].push_back(u);
}}

ll maxFlow(int s, int t) {
	int n = sz(adjlist);
	llist.assign(n + 1, {});
	dlist.assign(n + 1, {});
	highestActive = highest = 0;
	height.assign(n, 0);
	height[s] = n;
	iter.resize(n);
	for (int i = 0; i < n; i++) {
		if (i != s) iter[i] = dlist[height[i]].insert(dlist[height[i]].begin(), i);
	}
	ccount.assign(n, 0);
	ccount[0] = n-1;
	excess.assign(n, 0);
	excess[s] = inf;
	excess[t] = -inf;
	for (int id : adjlist[s]) push(s, id);
	globalRelabel(n, t);
	while (highestActive >= 0) {
		if (llist[highestActive].empty()) {
			highestActive--;
			continue;
		}
		int u = llist[highestActive].back();
		llist[highestActive].pop_back();
		discharge(n, u);
	}
	return excess[t] + inf;
}
