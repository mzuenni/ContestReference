vector<int> kmpPreprocessing(const string& sub) {
	vector<int> b(sz(sub) + 1);
	b[0] = -1;
	for (int i = 0, j = -1; i < sz(sub);) {
		while (j >= 0 && sub[i] != sub[j]) j = b[j];
		b[++i] = ++j;
	}
	return b;
}
vector<int> kmpSearch(const string& s, const string& sub) {
	vector<int> result, pre = kmpPreprocessing(sub);
	for (int i = 0, j = 0; i < sz(s);) {
		while (j >= 0 && s[i] != sub[j]) j = pre[j];
		i++; j++;
		if (j == sz(sub)) {
			result.push_back(i - j);
			j = pre[j];
	}}
	return result;
}
