string deBruijn(int n, char mi = '0', char ma = '1') {
	string res, c(1, mi);
	do {
		if (n % sz(c) == 0) res += c;
	} while(next(c, n, mi, ma));
	return res;
}
