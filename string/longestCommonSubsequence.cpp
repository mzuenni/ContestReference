string lcss(string& a, string& b) {
	vector<vector<int>> m(sz(a) + 1, vector<int>(sz(b) + 1));
	for(int y = sz(a) - 1; y >= 0; y--) {
		for(int x = sz(b) - 1; x >= 0; x--) {
			if(a[y] == b[x]) m[y][x] = 1 + m[y+1][x+1];
			else m[y][x] = max(m[y+1][x], m[y][x+1]);
	}} // Für die Länge: return m[0][0];
	string res; int x=0; int y=0;
	while(x < sz(b) && y < sz(a)) {
		if(a[y] == b[x]) res += a[y++], x++;
		else if(m[y][x+1] > m[y+1][x+1]) x++;
		else y++;
	}
	return res;
}
