vector<pt> convexHull(vector<pt> pts){
	sort(all(pts), [](const pt& a, const pt& b){
		return real(a) == real(b) ? imag(a) < imag(b)
		                          : real(a) < real(b);
	});
	pts.erase(unique(all(pts)), pts.end());
	int k = 0;
	vector<pt> h(2 * sz(pts));
	auto half = [&](auto begin, auto end, int t) {
		for (auto it = begin; it != end; it++) {
			while (k > t && cross(h[k-2], h[k-1], *it) <= 0) k--;
			h[k++] = *it;
	}};
	half(all(pts), 1);// Untere Hülle.
	half(next(pts.rbegin()), pts.rend(), k);// Obere Hülle.
	h.resize(k);
	return h;
}
