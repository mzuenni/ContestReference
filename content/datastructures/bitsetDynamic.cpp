#include <tr2/dynamic_bitset>
tr2::dynamic_bitset<unsigned ll> bits(N, 0b000010100);
bits.find_first()  //2
bits.find_next(2)  //4
bits.find_next(4)  //N
bits.append(0b111) //000..000111000..00010100
//resize(), clear(), push_back() like vector<bool>
//everything else like std::bitset
