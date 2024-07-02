#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

template<typename T>
struct betterHash {
	size_t operator()(T o) const {
		size_t h = hash<T>()(o) ^ 42394245; //random value
		h = ((h >> 16) ^ h) * 0x45d9f3b;
		h = ((h >> 16) ^ h) * 0x45d9f3b;
		h = ((h >> 16) ^ h);
		return h;
}};

template<typename K, typename V, typename H = betterHash<K>>
using hashMap = gp_hash_table<K, V, H>;
template<typename K, typename H = betterHash<K>>
using hashSet = gp_hash_table<K, null_type, H>;
