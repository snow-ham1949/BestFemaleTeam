// return (max subtree size, node ID)
int sizeSubT[N];
pair<int, int> Centroid(int u, int pa) {
  sizeSubT[u] = 1;
  pair<int, int> res(INT_MAX, -1);
  int mx = 0;
  for (int v : g[u]) {
    if (v == pa) continue;
    res = min(res, Centroid(v, u));
    sizesubT[u] += sizesubT[v];
    mx = max(mx, sizesubT[v]);
  }
  res = min(res, make_pair(max(mx, n - sizesubT[u]), u));
  return res;
}
