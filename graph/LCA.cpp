vector<vector<int>> adjlist();
vector<int> visited();
vector<int> first();
vector<int> depth();

void initLCA(int gi, int d, int& c) {
	visited[c] = gi, depth[c] = d, first[gi] = min(c, first[gi]), c++;
	for(int gn : adjlist[gi]) {
		initLCA(gn, d+1, c);
		visited[c] = gi, depth[c] = d, c++;
}}

int getLCA(int a, int b) {
	return visited[query(min(first[a], first[b]), max(first[a], first[b]))];
}

void exampleUse() {
	int c = 0;
	visited = vector<int>(2*sz(adjlist));
	first = vector<int>(sz(adjlist), 2*sz(adjlist));
	depth = vector<int>(2*sz(adjlist));
	initLCA(0, 0, c);
	init(depth);
}
