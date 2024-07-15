ll shortestDist(vector<pt> pts) { // sz(pts) > 1
	set<pt, bool(*)(pt, pt)> state([](pt a, pt b){
		return real(a) < real(b);
	});
	sort(all(pts), [](pt a, pt b){
		return imag(a) < imag(b);
	});
	ll opt = INF;
	int l = 0, r = 0;
	while (r < sz(pts)) {
		while (l < r &&
		    sq(imag(pts[l] - pts[r])) >= opt) {
			auto it = state.find(pts[l++]);
			if(*it == pts[l - 1]) state.erase(it);
		}
		//for floating point points use sqrtl
		auto lower = state.lower_bound(pts[r] - isqrt(opt));
		auto upper = state.upper_bound(pts[r] + isqrt(opt));
		for (;lower != upper; lower++) {
			opt = min(opt, norm(pts[r] - *lower));
		}
		auto it = state.find(pts[r]);
		if (it != state.end()) state.erase(it);
		state.insert(pts[r++]);
	}
	return opt;//sqrtl(opt);
}
