// Zahlenwerte müssen bei 0 beginnen und zusammenhängend sein.
constexpr int ALPHABET_SIZE = 2;
struct node {
	int words, ends;
	array<int, ALPHABET_SIZE> nxt;
	node() : words(0), ends(0) {fill(all(nxt), -1);}
};
vector<node> trie = {node()};

int traverse(const vector<int>& word, int x) {
	int id = 0;
	for (int c : word) {
		if (id < 0 || (trie[id].words == 0 && x <= 0)) return -1;
		trie[id].words += x;
		if (trie[id].nxt[c] < 0 && x > 0) {
			trie[id].nxt[c] = sz(trie);
			trie.emplace_back();
		}
		id = trie[id].nxt[c];
	}
	trie[id].words += x;
	trie[id].ends += x;
	return id;
}

int insert(const vector<int>& word) {
	return traverse(word, 1);
}

bool erase(const vector<int>& word) {
	int id = traverse(word, 0);
	if (id < 0 || trie[id].ends <= 0) return false;
	traverse(word, -1);
	return true;
}
