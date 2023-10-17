// x ≡ b_i (mod a_i), a_i is not promised to be mutually prime
ll mul(ll x, ll y, ll m) {
  ll res = 0;
  while (y) {
    if (y & 1) res = (res + x) % m;
    x = (x + x) % m;
    y >>= 1;
  }
  return res;
}
ll extgcd(ll a, ll b, ll &x, ll &y) {
  if (!b) { x = 1; y = 0; return a; }
  ll d = extgcd(b, a % b, y, x);
  y -= (a / b) * x;
  return d;
}
ll excrt() {
  ll clcm = a[0], res = b[0];
  for (int i = 1; i < n; i++) {
    ll x, y, d = extgcd(clcm, a[i], x, y);
    ll r = ((b[i] - res) % a[i] + a[i]) % a[i];
    ll tmp = clcm / d * a[i];
    if (r % d) return -1;
    x = (mul(x, r / d, a[i]) + a[i]) % a[i];
    res = (res + mul(x, clcm, tmp)) % tmp;
    clcm = tmp;
  }
  return res;
}
