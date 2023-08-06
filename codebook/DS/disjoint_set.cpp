struct DJS {
  int n;
  vector<int> p, sz;
  void init(int _n) {
    n = _n;
    p.resize(n);
    sz.assign(n, 1);
    iota(ALL(p), 0);
  }
  int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
  }
  bool _union(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (sz[x] > sz[y]) swap(x, y);
    p[x] = y;
    sz[y] += sz[x];
    return true;
  }
  bool same(int x, int y) {
    return find(x) == find(y);
  }
} djs;
