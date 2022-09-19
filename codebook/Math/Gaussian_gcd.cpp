typedef complex<ll> cpx;
cpx gaussian_gcd(cpx a, cpx b){
  #define rnd(a, b) ((a >= 0 ? a * 2 + b : a * 2 - b) / (b * 2))
  ll real = a.real() * b.real() + a.imag() * b.imag();
  ll imag = a.imag() * b.real() - a.real() * b.imag();
  ll scale = b.real() * b.real() + b.imag() * b.imag(); 
  if(real % scale == 0 && imag % scale == 0) return b;
  return gaussian_gcd(b, a - cpx(rnd(real, scale), (rnd(imag, scale))) * b);
}