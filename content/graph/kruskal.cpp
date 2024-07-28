sort(all(edges));
vector<Edge> mst;
ll cost = 0;
for (Edge& e : edges) {
	if (findSet(e.from) != findSet(e.to)) {
		unionSets(e.from, e.to);
		mst.push_back(e);
		cost += e.cost;
}}
