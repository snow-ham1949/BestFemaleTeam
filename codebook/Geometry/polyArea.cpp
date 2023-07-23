// using default code of Geometry
// includeing -, cross
double polyArea(vector<pdd> &v) {
  double res = 0.0;
  int n = SZ(v);
  for (int i = 1; i < n - 1; i++) res += cross(v[i] - v[0], v[i + 1] - v[0]);
  return res / 2.0;
}
