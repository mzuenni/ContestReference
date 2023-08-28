struct PushRelabel {
	vector<vector<ll>> capacitie, flow;
	vector<ll> excess;
	vector<int> height, seen, list;
	int n;

	PushRelabel(int n) {
		this->n = n;
		capacities.assign(n, vector<ll>(n));
		flow.assign(n, vector<ll>(n));
		excess.assign(n, 0);
		height.assign(n, 0);
		seen.assign(n, 0);
		list.assign(n - 2, 0);
	}

	inline void addEdge(int u, int v, ll c) {capacities[u][v] += c;}

	void push(int u, int v) {
		ll send = min(excess[u], capacities[u][v] - flow[u][v]);
		flow[u][v] += send; flow[v][u] -= send;
		excess[u] -= send; excess[v] += send;
	}

	void relabel(int v) {
		int minHeight = INT_INF;
		for (int u = 0; u < n; u++) {
			if (capacities[v][u] - flow[v][u] > 0) {
				minHeight = min(minHeight, height[u]);
				height[v] = minHeight + 1;
	}}}

	void discharge(int v) {
		while (excess[v] > 0) {
			if (seen[v] < n) {
				int u = seen[v];
				if (capacities[v][u] - flow[v][u] > 0 && height[v] > height[u]) {
					push(v, u);
				} else seen[v]++;
			} else {
				relabel(v);
				seen[v] = 0;
	}}}

	void moveToFront(int v) {
		int temp = list[v];
		for (int u = v; u > 0; u--) list[u] = list[u - 1];
		list[0] = temp;
	}

	ll maxFlow(int source, int target) {
		for (int v = 0, p = 0; v < n; v++)
			if (v != source && v != target) list[p++] = v;

		height[source] = n;
		excess[source] = INF;
		for (int v = 0; v < n; v++) push(source, v);

		int p = 0;
		while (p < n - 2) {
			int v = list[p], oldHeight = height[v];
			discharge(v);
			if (height[v] > oldHeight) {
				moveToFront(p);
				p = 0;
			} else p++;
		}

		ll maxflow = 0;
		for (int v = 0; v < n; v++) maxflow += flow[source][v];
		return maxflow;
	}
};
