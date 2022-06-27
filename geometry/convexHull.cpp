vector<pt> convexHull(vector<pt> p){
	sort(p.begin(), p.end(), [](const pt& a, const pt& b){
		return real(a) == real(b) ? imag(a) < imag(b)
															: real(a) < real(b);
	});
	p.erase(unique(p.begin(), p.end()), p.end());
	int k = 0;
	vector<pt> h(2 * sz(p));
	for (int i = 0; i < sz(p); i++) {// Untere Hülle.
		while (k > 1 && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
		h[k++] = p[i];
	}
	for (int i = sz(p)-2, t = k; i >= 0; i--) {// Obere Hülle.
		while (k > t && cross(h[k-2], h[k-1], p[i]) <= 0) k--;
		h[k++] = p[i];
	}
	h.resize(k);
	return h;
}
