template<typename F>
ld gss(ld l, ld r, F&& f) {
	ld inv = (sqrt(5.0l) - 1) / 2;
	ld x1 = r - inv*(r-l), x2 = l + inv*(r-l);
	ld f1 = f(x1), f2 = f(x2);
	for (int i = 0; i < 200; i++) {
		if (f1 < f2) { //change to > to find maximum
			r = x2; x2 = x1; f2 = f1;
			x1 = r - inv*(r-l); f1 = f(x1);
		} else {
			l = x1; x1 = x2; f1 = f2;
			x2 = l + inv*(r-l); f2 = f(x2);
	}}
	return l;
}
