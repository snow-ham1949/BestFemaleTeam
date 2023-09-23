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
