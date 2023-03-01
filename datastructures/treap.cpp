struct node {
	int key, prio, left, right, size;
	node(int key, int prio) : key(key), prio(prio), left(-1),
	                          right(-1), size(1) {};
};

vector<node> treap;

int getSize(int root) {
	return root < 0 ? 0 : treap[root].size;
}

void update(int root) {
	if (root < 0) return;
	treap[root].size = 1 + getSize(treap[root].left)
	                     + getSize(treap[root].right);
}

pair<int, int> split(int root, int minKeyRight) {
	if (root < 0) return {-1, -1};
	if (treap[root].key >= minKeyRight) {
		auto leftSplit = split(treap[root].left, minKeyRight);
		treap[root].left = leftSplit.second;
		update(root);
		leftSplit.second = root;
		return leftSplit;
	} else {
		auto rightSplit = split(treap[root].right, minKeyRight);
		treap[root].right = rightSplit.first;
		update(root);
		rightSplit.first = root;
		return rightSplit;
}}

int merge (int left, int right) {
	if (left < 0) return right;
	if (right < 0) return left;
	if (treap[left].prio < treap[right].prio) { //min priority heap
		treap[left].right = merge(treap[left].right, right);
		update(left);
		return left;
	} else {
		treap[right].left = merge(left, treap[right].left);
		update(right);
		return right;
}}

//insert values with high priority first
int insert(int root, int key, int prio) {
	int next = sz(treap);
	treap.emplace_back(key, prio);
	auto t = split(root, key);
	//returns new root
	return merge(merge(t.first, next), t.second);
}

int remove(int root, int key) {
	if (root < 0) return -1;
	if (key < treap[root].key) {
		treap[root].left = remove(treap[root].left, key);
		update(root);
		return root;
	} else if (key > treap[root].key) {
		treap[root].right = remove(treap[root].right, key);
		update(root);
		return root;
	} else { //check prio?
		return merge(treap[root].left, treap[root].right);
}}

int kth(int root, int k) {
	if (root < 0) return -1;
	int leftSize = getSize(treap[root].left);
	if (k < leftSize) return kth(treap[root].left, k);
	else if (k > leftSize) {
		return kth(treap[root].right, k - 1 - leftSize);
	}
	return root;
}
