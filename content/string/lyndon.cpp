bool next(string& s, int maxLen, char mi = '0', char ma = '1') {
	for (int i = sz(s), j = sz(s); i < maxLen; i++)
		s.push_back(s[i % j]);
	while(!s.empty() && s.back() == ma) s.pop_back();
	if (s.empty()) {
		s = mi;
		return false;
	} else {
		s.back()++;
		return true;
}}
