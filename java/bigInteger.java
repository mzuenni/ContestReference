// Berechnet this +,*,/,- val.
BigInteger add(BigInteger val), multiply(BigInteger val),
					 divide(BigInteger val), substract(BigInteger val)

// Berechnet this^e.
BigInteger pow(BigInteger e)

// Bit-Operationen.
BigInteger and(BigInteger val), or(BigInteger val), xor(BigInteger val),
		   not(), shiftLeft(int n), shiftRight(int n)

// Berechnet den ggT von abs(this) und abs(val).
BigInteger gcd(BigInteger val)

// Berechnet this mod m, this^-1 mod m, this^e mod m.
BigInteger mod(BigInteger m), modInverse(BigInteger m),
					 modPow(BigInteger e, BigInteger m)

// Berechnet die nächste Zahl, die größer und wahrscheinlich prim ist.
BigInteger  nextProbablePrime()

// Berechnet int/long/float/double-Wert.
// Ist die Zahl zu großen werden die niedrigsten Bits konvertiert.
int intValue(), long longValue(),
float floatValue(), double doubleValue() 