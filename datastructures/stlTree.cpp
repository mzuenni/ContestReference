#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std; using namespace __gnu_pbds;
template<typename T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;

int main() {
	Tree<int> X;
	for (int i : {1, 2, 4, 8, 16}) X.insert(i);
	*X.find_by_order(3); // => 8
	X.order_of_key(10);  // => 4 = min i, mit X[i] >= 10
}
