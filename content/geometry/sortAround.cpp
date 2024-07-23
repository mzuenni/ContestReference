bool left(pt p) {return real(p) < 0 || 
                       (real(p) == 0 && imag(p) < 0);}

// counter clockwise, starting with "11:59"
void sortAround(pt p, vector<pt>& ps) {
	sort(all(ps), [&](const pt& a, const pt& b){
		if (left(a - p) != left(b - p)) 
			return left(a - p) > left(b - p);
		return cross(p, a, b) > 0;
	});
}
