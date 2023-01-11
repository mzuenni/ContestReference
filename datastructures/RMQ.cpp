vector<int> values;
vector<vector<int>> rmq;

int select(int a, int b) {
	return values[a] <= values[b] ? a : b;
}

void build() {
	for(int i = 0, s = 1, ss = 1; s <= sz(values); ss=s, s*=2, i++) {
		for(int l = 0; l + s <= sz(values); l++) {
			if(i == 0) rmq[0][l] = l;
			else {
				int r = l + ss;
				rmq[i][l] = select(rmq[i-1][l], rmq[i-1][r]]);
}}}}

void init(const vector<int>& v) {
	values = v;
	rmq = vector<vector<int>>(__lg(sz(values))+1, vector<int>(sz(values)));
	build();
}

int query(int l, int r) {
	if(l >= r) return l;
	int s = __lg(r-l); r = r - (1 << s);
	return select(rmq[s][l],rmq[s][r]);
}