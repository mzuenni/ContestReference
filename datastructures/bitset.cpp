bitset<10> bits(0b000010100);
cout << bits._Find_first() << endl; //2
cout << bits._Find_next(2) << endl; //4
cout << bits._Find_next(4) << endl; //10 bzw. N
bits[x] = 1;    //not bits.set(x)!
bits[x] = 0;    //not bits.reset(x)!
bits[x].flip(); //not bits.flip(x)!
