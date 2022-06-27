// Zahlenwerte müssen bei 0 beginnen und zusammenhängend sein.
constexpr int ALPHABET_SIZE = 2;
struct node {
	int words, wordEnds; vector<int> children;
	node() : words(0), wordEnds(0), children(ALPHABET_SIZE, -1){}
};
vector<node> trie = {node()};

int insert(vector<int>& word) {
	int id = 0;
	for (int c : word) {
		trie[id].words++;
		if (trie[id].children[c] < 0) {
			trie[id].children[c] = trie.size();
			trie.emplace_back();
		}
		id = trie[id].children[c];
	}
	trie[id].words++;
	trie[id].wordEnds++;
	return id;
}

void erase(vector<int>& word) {
	int id = 0;
	for (int c : word) {
		trie[id].words--;
		id = trie[id].children[c];
		if (id < 0) return;
	}
	trie[id].words--;
	trie[id].wordEnds--;
}
