vector<pair<int, int>> duval(const string& s) {
	vector<pair<int, int>> res;
	for (int i = 0; i < sz(s);) {
		int j = i + 1, k = i;
		for (; j < sz(s) && s[k] <= s[j]; j++) {
			if (s[k] < s[j]) k = i;
			else k++;
		}
		for (; i <= k; i += j - k) {
			res.push_back({i, i + j - k});
	}}
	return res;
}

int minrotation(const string& s) {
	auto parts = duval(s+s);
	for (auto [l, r] : parts) {
		if (r >= sz(s)) return l;
}}
