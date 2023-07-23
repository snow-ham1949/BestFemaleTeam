// using default code of Geometry
// including -, cross, abs2
double rotating_calipers(vector<pdd> &hull) {
  // find pair which has longest distance
  double ans = 0.0;
  int t = 1;
  int sz = SZ(hull);
  hull.push_back(hull[0]);
  for (int i = 0; i < sz; i++) {
    while (cross(hull[i + 1] - hull[i], hull[t + 1] - hull[i]) > cross(hull[i + 1] - hull[i], hull[t] - hull[i])) t = (t + 1) % sz;
    ans = max(ans, max(abs2(hull[i] - hull[t]), abs2(hull[i + 1] - hull[t + 1])));
  }
  return ans;
}

