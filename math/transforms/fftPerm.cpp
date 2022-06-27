int perm[MAXN]; //perm[i] = j in Zeile 10
void genPerm(int n){
	ull mask = ~0ull << (__lg(n) - 1);
	for (int i = 0, j = 0; i < n; i++) {
		perm[i] = j; //if (i < j) swap(a[i], a[j]);
		ull y = mask >> __builtin_ctz(~i);
		j ^= y & (n - 1);
}}
