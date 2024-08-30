int rotateLeft(int n) { // Der letzte Überlebende, 1-basiert.
	int bits = __lg(n);
	n ^= 1 << bits;
	return 2 * n + 1;
}
