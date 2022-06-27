double squaredDist(pt a, pt b) {
	return real(conj(a-b) * (a-b));
}

bool compY(pt a, pt b) {
	return (imag(a) == imag(b)) ? real(a) < real(b) 
															: imag(a) < imag(b);
}

bool compX(pt a, pt b) {
	return (real(a) == real(b)) ? imag(a) < imag(b)
															: real(a) < real(b);
}

double shortestDist(vector<pt>& points) { // points.size() > 1
	set<pt, bool(*)(pt, pt)> status(compY);
	sort(points.begin(), points.end(), compX);
	double opt = 1.0/0.0, sqrtOpt = 1.0/0.0;
	auto left = points.begin(), right = points.begin();
	status.insert(*right); right++;

	while (right != points.end()) {
		if (left != right &&
				abs(real(*left - *right)) >= sqrtOpt) {
			status.erase(*left);
			left++;
		} else {
			auto lower = status.lower_bound({-1.0/0.0, imag(*right) - sqrtOpt});
			auto upper = status.upper_bound({-1.0/0.0, imag(*right) + sqrtOpt});
			for (;lower != upper; lower++) {
				double cand = squaredDist(*right, *lower);
				if (cand < opt) {
					opt = cand;
					sqrtOpt = sqrt(opt);
			}}
			status.insert(*right);
			right++;
	}}
	return sqrtOpt;
}
