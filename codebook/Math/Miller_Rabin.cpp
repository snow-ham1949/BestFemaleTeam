// choices of a
// n < 4,759,123,141 3 : 2, 7, 61
// n < 1,122,004,669,633 4 : 2, 13, 23, 1662803
// n < 3,474,749,660,383 6 : primes <= 13
// n < 2^64 7 :
// 2, 325, 9375, 28178, 450775, 9780504, 1795265022

typedef unsigned long long int ull;
using u128 = __uint128_t;

bool Miller_Rabin(ull a, ull n){
  if(n < 2) return 0;
  if((a %= n) == 0) return true;
  if(n % 2 == 0) return n == 2;
  // n - 1 = 2^s * d
  ull d = (n-1) / ((n-1)&(1-n));
  ull s = __lg((n-1)&(1-n));
  ull x = 1;
  // x = a^d
  while(d){
    if(d&1)
      x = (u128)x * a % n;
    d >>= 1;
    a = (u128)a * a % n;
  }
  if(x == 1 || x == n-1) return true;
  while(--s){
    if ((x = (u128)x * x % n) == n - 1) return true;
  }
  return false;
}
