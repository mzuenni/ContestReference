struct PushRelabel {
	vector<vector<long long>> capacitie, flow;
	vector<long long> excess;
	vector<int> height, seen, list;
	int n;

	PushRelabel(int n) {
		this->n = n;
		capacities.assign(n, vector<long long>(n));
		flow.assign(n, vector<long long>(n));
		excess.assign(n, 0);
		height.assign(n, 0);
		seen.assign(n, 0);
		list.assign(n - 2, 0);
	}

	inline void addEdge(int u, int v, long long c) {capacities[u][v] += c;}

	void push(int u, int v) {
		long long send = min(excess[u], capacities[u][v] - flow[u][v]);
		flow[u][v] += send; flow[v][u] -= send;
		excess[u] -= send; excess[v] += send;
	}

	void relabel(int u) {
		int minHeight = INT_INF;
		for (int v = 0; v < n; v++) {
			if (capacities[u][v] - flow[u][v] > 0) {
				minHeight = min(minHeight, height[v]);
				height[u] = minHeight + 1;
	}}}

	void discharge(int u) {
		while (excess[u] > 0) {
			if (seen[u] < n) {
				int v = seen[u];
				if (capacities[u][v] - flow[u][v] > 0 && height[u] > height[v]) {
					push(u, v);
				} else seen[u]++;
			} else {
				relabel(u);
				seen[u] = 0;
	}}}

	void moveToFront(int u) {
		int temp = list[u];
		for (int i = u; i > 0; i--) list[i] = list[i - 1];
		list[0] = temp;
	}

	long long maxFlow(int source, int target) {
		for (int i = 0, p = 0; i < n; i++)
			if (i != source && i != target) list[p++] = i;

		height[source] = n;
		excess[source] = INF;
		for (int i = 0; i < n; i++) push(source, i);

		int p = 0;
		while (p < n - 2) {
			int u = list[p], oldHeight = height[u];
			discharge(u);
			if (height[u] > oldHeight) {
				moveToFront(p);
				p = 0;
			} else p++;
		}

		long long maxflow = 0;
		for (int i = 0; i < n; i++) maxflow += flow[source][i];
		return maxflow;
	}
};
