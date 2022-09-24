// find [x, y] such that ax + by = 1;
pll extgcd(ll a, ll b) {
  if (b == 0) return pll(1, 0);
  pll p = extgcd(b, a % b);
  return pll(p.second, p.first - p.second * (a / b));
}
