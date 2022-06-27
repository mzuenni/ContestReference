vector<int> kmpPreprocessing(const string& sub) {
	vector<int> b(sub.size() + 1);
	b[0] = -1;
	int i = 0, j = -1;
	while (i < (int)sub.size()) {
		while (j >= 0 && sub[i] != sub[j]) j = b[j];
		i++; j++;
		b[i] = j;
	}
	return b;
}
vector<int> kmpSearch(const string& s, const string& sub) {
	vector<int> pre = kmpPreprocessing(sub), result;
	int i = 0, j = 0;
	while (i < (int)s.size()) {
		while (j >= 0 && s[i] != sub[j]) j = pre[j];
		i++; j++;
		if (j == (int)sub.size()) {
			result.push_back(i - j);
			j = pre[j];
	}}
	return result;
}
