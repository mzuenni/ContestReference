vector<vector<vector<int>>>
getTreeLabel(const vector<vector<int>>& adj, int root) {
	vector<vector<int>> level = {{root}};
	vector<int> dist(sz(adj), -1);
	dist[root] = 0;
	queue<int> q;
	q.push(root);
	while (!q.empty()) {
		int c = q.front();
		q.pop();
		for (int n : adj[c]) {
			if (dist[n] < 0) {
				dist[n] = dist[c] + 1;
				if (sz(level) <= dist[n]) level.push_back({});
				level[dist[n]].push_back(n);
				q.push(n);
	}}}
	
	vector<vector<vector<int>>> levelLabels(sz(level));
	vector<int> shortLabel(sz(adj));
	for (int l = sz(level) - 1; l >= 0; l--) {
		vector<pair<vector<int>, int>> tmpLabels;
		for (int v : level[l]) {
			vector<int> label;
			for (int n : adj[v]) {
				if (dist[n] > dist[v]) {
					label.push_back(shortLabel[n]);
			}}
			sort(all(label));
			tmpLabels.push_back({label, v});
		}
		sort(all(tmpLabels));
		vector<int>& last = tmpLabels[0].first;
		int curId = 0;
		for (auto& e : tmpLabels) {
			levelLabels[l].push_back(e.first);
			if (e.first != last) curId++, last = e.first;
			shortLabel[e.second] = curId;
	}}
	return levelLabels;
} 
