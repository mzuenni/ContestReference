constexpr ll queryDefault = 0;
constexpr ll updateDefault = 0;

ll _modify(ll x, ll y) {
	return x + y;
}

ll _query(ll x, ll y) {
	return x + y;
}

ll _update(ll delta, int length) {
	if (delta == updateDefault) return updateDefault;
	//ll result = delta
	//for (int i=1; i<length; i++) result = _query(result, delta);
	return delta * length;
}

//generic:
ll joinValueDelta(ll value, ll delta) {
	if (delta == updateDefault) return value;
	return _modify(value, delta);
}

ll joinDeltas(ll delta1, ll delta2) {
	if (delta1 == updateDefault) return delta2;
	if (delta2 == updateDefault) return delta1;
	return _modify(delta1, delta2);
}

struct LCT {
	struct Node {
		ll nodeValue, subTreeValue, delta;
		bool revert;
		int id, size;
		Node *left, *right, *parent;

		Node(int id = 0, int val = queryDefault) :
			nodeValue(val), subTreeValue(val), delta(updateDefault),
			revert(false), id(id), size(1),
			left(nullptr), right(nullptr), parent(nullptr) {}

		bool isRoot() {
			return !parent || (parent->left != this &&
			                   parent->right != this);
		}

		void push() {
			if (revert) {
				revert = false;
				swap(left, right);
				if (left) left->revert ^= 1;
				if (right) right->revert ^= 1;
			}
			nodeValue = joinValueDelta(nodeValue, delta);
			subTreeValue = joinValueDelta(subTreeValue,
			                              _update(delta, size));
			if (left) left->delta = joinDeltas(left->delta, delta);
			if (right) right->delta = joinDeltas(right->delta, delta);
			delta = updateDefault;
		}

		ll getSubtreeValue() {
			return joinValueDelta(subTreeValue, _update(delta, size));
		}

		void update() {
			subTreeValue = joinValueDelta(nodeValue, delta);
			size = 1;
			if (left) {
				subTreeValue = _query(subTreeValue,
				                      left->getSubtreeValue());
				size += left->size;
			}
			if (right) {
				subTreeValue = _query(subTreeValue,
				                      right->getSubtreeValue());
				size += right->size;
		}}
	};

	vector<Node> nodes;

	LCT(int n) : nodes(n) {
		for (int i = 0; i < n; i++) nodes[i].id = i;
	}

	void connect(Node* ch, Node* p, int isLeftChild) {
		if (ch) ch->parent = p;
		if (isLeftChild >= 0) {
			if (isLeftChild) p->left = ch;
			else p->right = ch;
	}}

	void rotate(Node* x) {
		Node* p = x->parent;
		Node* g = p->parent;
		bool isRootP = p->isRoot();
		bool leftChildX = (x == p->left);

		connect(leftChildX ? x->right : x->left, p, leftChildX);
		connect(p, x, !leftChildX);
		connect(x, g, isRootP ? -1 : p == g->left);
		p->update();
	}

	void splay(Node* x) {
		while (!x->isRoot()) {
			Node* p = x->parent;
			Node* g = p->parent;
			if (!p->isRoot()) g->push();
			p->push();
			x->push();
			if (!p->isRoot()) rotate((x == p->left) ==
			                         (p == g->left) ?  p : x);
			rotate(x);
		}
		x->push();
		x->update();
	}

	Node* expose(Node* x) {
		Node* last = nullptr;
		for (Node* y = x; y; y = y->parent) {
			splay(y);
			y->left = last;
			last = y;
		}
		splay(x);
		return last;
	}

	void makeRoot(Node* x) {
		expose(x);
		x->revert ^= 1;
	}

	bool connected(Node* x, Node* y) {
		if (x == y) return true;
		expose(x);
		expose(y);
		return x->parent;
	}

	void link(Node* x, Node* y) {
		assert(!connected(x, y)); // not yet connected!
		makeRoot(x);
		x->parent = y;
	}

	void cut(Node* x, Node* y) {
		makeRoot(x);
		expose(y);
		//must be a tree edge!
		assert(!(y->right != x || x->left != nullptr));
		y->right->parent = nullptr;
		y->right = nullptr;
	}

	Node* lca(Node* x, Node* y) {
		assert(connected(x, y));
		expose(x);
		return expose(y);
	}

	ll query(Node* from, Node* to) {
		makeRoot(from);
		expose(to);
		if (to) return to->getSubtreeValue();
		return queryDefault;
	}

	void modify(Node* from, Node* to, ll delta) {
		makeRoot(from);
		expose(to);
		to->delta = joinDeltas(to->delta, delta);
	}
};
