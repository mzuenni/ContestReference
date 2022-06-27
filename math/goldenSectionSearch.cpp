ld gss(ld l, ld r, function<ld(ld)> f) {
	ld r = (sqrtl(5.0l)-1)/2;
	ld x1 = b - r*(b-a), x2 = a + r*(b-a);
	ld f1 = f(x1), f2 = f(x2);
	for (int i = 0; i < 200; i++) {
		if (f1 < f2) { //change to > to find maximum
			b = x2; x2 = x1; f2 = f1;
			x1 = b - r*(b-a); f1 = f(x1);
		} else {
			a = x1; x1 = x2; f1 = f2;
			x2 = a + r*(b-a); f2 = f(x2);
	}}
	return a;
}
