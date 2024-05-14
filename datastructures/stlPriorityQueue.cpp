#include <ext/pb_ds/priority_queue.hpp>
template<typename T>
using pQueue = __gnu_pbds::priority_queue<T>; //<T, greater<T>>

auto it = pq.push(5);
pq.modify(it, 6);
pq.join(pq2);
// push, join are O(1), pop, modify, erase O(log n) amortized
