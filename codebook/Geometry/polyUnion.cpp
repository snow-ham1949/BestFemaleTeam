// using default code of Geometry
// including -, sign, cross, dot

#define mp make_pair

double seg(pdd &o, pdd &a, pdd &b) {
  if (sign(b.X - a.X) == 0) return (o.Y - a.Y) / (b.Y - a.Y);
  return (o.X - a.X) / (b.X - a.X);
}

double polyUnion(vector<vector<pdd>> &v) {
  int n = SZ(v); // number of polygons
  double res = 0.0;
  pair<double, int> s[(n + 10) * 60];
  for (int i = 0; i < n; i++) {
    int sz = SZ(v[i]);
    for (int j = 0; j < sz; j++ ) {
      int m = 0;
      s[m++] = mp(0.0, 0);
      s[m++] = mp(1.0, 0);
      pdd a = v[i][j], b = v[i][(j + 1) % sz];
      for (int k = 0; k < n; k++) {
        if (i != k) {
          int sz2 = SZ(v[k]);
          for (int ii = 0; ii < sz2; ii++) {
            pdd c = v[k][ii], d = v[k][(ii + 1) % sz2];
            int c1 = sign(cross(b - a, c - a));
            int c2 = sign(cross(b - a, d - a));
            if (c1 == c2) {
              if (sign(dot(b - a, d - c))) {
                s[m++] = mp(seg(c, a, b), 1);
                s[m++] = mp(seg(c, a, b), -1);
              }
            } else {
              double s1 = cross(d - c, a - c);
              double s2 = cross(d - c, b - c);
              if (c1 >= 0 && c2 < 0) s[m++] = mp(s1 / (s1 - s2), 1);
              else if (c1 < 0 && c2 >= 0) s[m++] = mp(s1 / (s1 - s2), -1);
            }
          }
        }
      }
      sort(s, s + m);
      double pre = min(max(s[0].X, 0.0), 1.0), sum = 0, now;
      int cov = s[0].Y;
      for (int k = 1; k < m; k++) {
        now = min(max(s[k].X, 0.0), 1.0);
        if (!cov) sum += (now - pre);
        cov += s[k].Y;
        pre = now;
      }
      res += cross(a, b) * sum;
    }
  }
  return res / 2.0;
}
