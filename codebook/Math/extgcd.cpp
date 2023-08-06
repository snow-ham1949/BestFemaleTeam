// find [x, y] such that ax + by = 1;
ll extgcd(ll a, ll b, ll &x, ll &y) {
  if (!b) { x = 1; y = 0; return a; }
  ll d = extgcd(b, a % b, y, x);
  y -= (a / b) * x;
  return d;
}
