// construct
bitset<128> b; // 128 is length
bitset<128> b(42);
bitset<128> b("01010");
// bit access
b[1] // asscess bit
b.count() // return number of 1
b.size() // return length
b.any() // true if at least one of the bits is set
b.none() // true if none of the bits is set
b.all() // true if all of the bits are set
// bit manipulation
b.to_string(ZERO, ONE) // ZERO: character to use to represent false, default '0', ONE; character to use to represent true, default '1'
b.to_ulong()
b.to_ullong()
// bit operations
// can set all bits or single bit
b.set() 
b.reset()
b.flip()
