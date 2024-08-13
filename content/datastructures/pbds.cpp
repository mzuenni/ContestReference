#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
// T.order_of_key(x): number of elements strictly less than x
// *T.find_by_order(k): k-th element

constexpr uint64_t RNG = ll(2e18 * acos(-1)) | 199; // random odd
template<typename T>
struct chash {
	size_t operator()(T o) const {
		return __builtin_bswap64(hash<T>()(o) * RNG);
}};
template<typename K, typename V>
using hashMap = gp_hash_table<K, V, chash<K>>;
template<typename T>
using hashSet = gp_hash_table<T, null_type, chash<T>>;
