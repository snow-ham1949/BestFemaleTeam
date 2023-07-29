struct DJS {
  int n;
  vector<int> p, sz;
  void init(_n) {
    n = _n;
    p.resize(n);
    sz.assign(n, 1);
    iota(ALL(p), 0);
  }
  int find(int x) {
    return p[x] == x ? x : p[x] = find(p[x]);
  }
  void _union(int x, int y) {
    int px = find(x), py = find(y);
    if (sz[px] > sz[py]) swap(px, py);
    p[x] = y;
    sz[py] += sz[px];
  }
} djs;
