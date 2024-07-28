bitset<10> bits(0b000010100);
bits._Find_first(); //2
bits._Find_next(2); //4
bits._Find_next(4); //10 bzw. N
bits[x] = 1;        //not bits.set(x) or bits.reset(x)!
bits[x].flip();     //not bits.flip(x)!
bits.count();       //number of set bits
