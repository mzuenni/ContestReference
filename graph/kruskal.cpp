sort(all(edges));
vector<edge> mst;
ll cost = 0;
for (edge& e : edges) {
	if (findSet(e.from) != findSet(e.to)) {
		unionSets(e.from, e.to);
		mst.push_back(e);
		cost += e.cost;
}}
