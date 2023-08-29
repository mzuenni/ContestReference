constexpr ll inf = 1ll<<60;

struct Edge {
	int from, to;
	ll f, c;
};

vector<Edge> edges;
vector<vector<int>> adj, llist;
vector<int> height, ccount, que;
vector<ll> excess;
vector<list<int>> dlist;
vector<list<int>::iterator> iter;
int highest, highestActive;

void addEdge(int from, int to, ll c) {
	adj[from].push_back(sz(edges));
	edges.push_back({from, to, 0, c});
	adj[to].push_back(sz(edges));
	edges.push_back({to, from, 0, 0});
}

void globalRelabel(int n, int t) {
	height.assign(n, n);
	height[t] = 0;
	ccount.assign(n, 0);
	que.assign(n+1, 0);
	int qh = 0, qt = 0;
	for (que[qt++] = t; qh < qt;) {
		int v = que[qh++], h = height[v] + 1;
		for (int id : adj[v]) {
			if (height[edges[id].to] == n && edges[id ^ 1].c - edges[id ^ 1].f > 0) {
				ccount[height[edges[id].to] = h]++;
				que[qt++] = edges[id].to;
	}}}
	llist.assign(n+1, {});
	dlist.assign(n+1, {});
	for (int v = 0; v < n; v++) {
		if (height[v] < n) {
			iter[v] = dlist[height[v]].insert(dlist[height[v]].begin(), v);
			if (excess[v] > 0) llist[height[v]].push_back(v);
	}}
	highest = highestActive = height[que[qt - 1]];
}

void push(int v, int id) {
	int u = edges[id].to;
	ll df = min(excess[v], edges[id].c - edges[id].f);
	edges[id].f += df;
	edges[id^1].f -= df;
	excess[v] -= df;
	excess[u] += df;
	if (0 < excess[u] && excess[u] <= df) llist[height[u]].push_back(u);
}

void discharge(int n, int v) {
	int nh = n;
	for (int id : adj[v]) {
		if (edges[id].c - edges[id].f > 0) {
			if (height[v] == height[edges[id].to] + 1) {
				push(v, id);
				if (!excess[v]) return;
			} else {
				nh = min(nh, height[edges[id].to] + 1);
	}}}
	int h = height[v];
	if (ccount[h] == 1) {
		for (int i = h; i <= highest; i++) {
			for (auto p : dlist[i]) --ccount[height[p]], height[p] = n;
			dlist[i].clear();
		}
		highest = h - 1;
	} else {
		--ccount[h], iter[v] = dlist[h].erase(iter[v]), height[v] = nh;
		if (nh == n) return;
		++ccount[nh], iter[v] = dlist[nh].insert(dlist[nh].begin(), v);
		highest = max(highest, highestActive = nh);
		llist[nh].push_back(v);
}}

ll maxFlow(int s, int t) {
	int n = sz(adj);
	llist.assign(n + 1, {});
	dlist.assign(n + 1, {});
	highestActive = highest = 0;
	height.assign(n, 0);
	height[s] = n;
	iter.resize(n);
	for (int v = 0; v < n; v++) {
		if (v != s) iter[v] = dlist[height[v]].insert(dlist[height[v]].begin(), v);
	}
	ccount.assign(n, 0);
	ccount[0] = n-1;
	excess.assign(n, 0);
	excess[s] = inf;
	excess[t] = -inf;
	for (int id : adj[s]) push(s, id);
	globalRelabel(n, t);
	while (highestActive >= 0) {
		if (llist[highestActive].empty()) {
			highestActive--;
			continue;
		}
		int v = llist[highestActive].back();
		llist[highestActive].pop_back();
		discharge(n, v);
	}
	return excess[t] + inf;
}
