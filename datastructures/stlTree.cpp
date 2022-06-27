#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std; using namespace __gnu_pbds;
template<typename T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
									tree_order_statistics_node_update>;

int main() {
	Tree<int> X;
	// insert {1, 2, 4, 8, 16}
	for (int i = 1; i <= 16; i *= 2) X.insert(i);
	cout << *X.find_by_order(3) << endl; // => 8
	cout << X.order_of_key(10) << endl;
	// => 4 = min i, mit X[i] >= 10
	return 0;
}
