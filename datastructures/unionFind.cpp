// unions[i] >= 0 => unions[i] =  parent
// unions[i]  < 0 => unions[i] = -size
vector<int> unions;

void init(int n) { //Initialisieren
	unions.assign(n, -1);
}

int findSet(int n) { // Pfadkompression
	if (unions[n] < 0) return n;
	return unions[n] = findSet(unions[n]);
}

void linkSets(int a, int b) { // Union by size.
	if (unions[b] > unions[a]) swap(a, b);
	unions[b] += unions[a];
	unions[a] = b;
}

void unionSets(int a, int b) { // Diese Funktion aufrufen.
	if (findSet(a) != findSet(b)) linkSets(findSet(a), findSet(b));
}

int size(int a) {
	return -unions[findSet(a)];
}
