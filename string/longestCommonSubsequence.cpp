string lcss(string& a, string& b) {
	vector<vector<int>> m(a.size() + 1, vector<int>(b.size() + 1));
	for(int y = a.size() - 1; y >= 0; y--) {
		for(int x = b.size() - 1; x >= 0; x--) {
			if(a[y] == b[x]) m[y][x] = 1 + m[y+1][x+1];
			else m[y][x] = max(m[y+1][x], m[y][x+1]);
	}} // Für die Länge: return m[0][0];
	string res; int x=0; int y=0;
	while(x < b.size() && y < a.size()) {
		if(a[y] == b[x]) res += a[y++], x++;
		else if(m[y][x+1] > m[y+1][x+1]) x++;
		else y++;
	}
	return res;
}
