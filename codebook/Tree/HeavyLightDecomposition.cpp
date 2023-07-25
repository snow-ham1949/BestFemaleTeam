struct Heavy_light_Decomposition { // 1-base
  // ulink[i]: the head of i-th path
  int n, ulink[MAXN], deep[MAXN], mxson[MAXN], size[MAXN], pa[MAXN];
  // dt[i]: weight on node[i]'s edge to its parent (data of node[i])
  // bln[i]:edge[i]'s node's order of dfs (index in seg tree)
  // pl[i]: node[i]'s order of dfs (index in seg tree)
  // data[i]: dt[segtree[i]]
  int t, pl[MAXN], bln[MAXN], edge[MAXN], et;
  vector<int> data, dt;
  vector<pii> G[MAXN];
  void init(int _n) {
    n = _n, t = 0, et = 1;
    for (int i = 1; i <= n; ++i){
      G[i].clear(), mxson[i] = 0;
    }
    data.resize(n+1), dt.resize(n+1);
  }
  void add_edge(int a, int b, int w=0) {
    G[a].push_back(pii(b, et));
    G[b].push_back(pii(a, et));
    edge[et++] = w;
  }
  void dfs(int u, int f, int d) {
    size[u] = 1, pa[u] = f, deep[u] = d++;
    for (auto &i : G[u])
      if (i.X != f) {
        dfs(i.X, u, d), size[u] += size[i.X];
        if (size[mxson[u]] < size[i.X]) mxson[u] = i.X;
      } //else bln[i.Y] = u, dt[u] = edge[i.Y];
  }
  void cut(int u, int link) {
    data[pl[u] = t++] = dt[u], ulink[u] = link;
    if (!mxson[u]) return;
    cut(mxson[u], link);
    for (auto i : G[u])
      if (i.X != pa[u] && i.X != mxson[u])
        cut(i.X, i.X);
  }
  void build(int root) { 
    dfs(root, root, 1); 
    cut(root, root);
    seg.build(data, n);
  }

  void update(int a, int b, int c){
    c %= mod;
    int ta = ulink[a], tb = ulink[b];
    while(ta != tb){
      if(deep[ta] < deep[tb]){
        seg.update(pl[tb], pl[b], c);
        tb = ulink[b = pa[tb]];
      } else {
        seg.update(pl[ta],pl[a], c);
        ta = ulink[a = pa[ta]];
      }
    }
    if (pl[a] > pl[b]) swap(a, b);
    seg.update(pl[a], pl[b], c);
  }

  int query(int a, int b) {
    int ta = ulink[a], tb = ulink[b];
    int re = 0;
    while (ta != tb){
      if (deep[ta] < deep[tb]) {
        re = re + seg.query(pl[tb], pl[b]);
        tb = ulink[b = pa[tb]];
      } else {
        re = re + seg.query(pl[ta], pl[a]);
        ta = ulink[a = pa[ta]];
      }
    }
    if (pl[a] > pl[b]) swap(a, b);
    re = re + seg.query(pl[a], pl[b]);
    return re;
  }

  void pure_update(int x, int z){
    seg.update(pl[x], pl[x]+size[x]-1, z);
  }

  int pure_query(int x){
    return seg.query(pl[x], pl[x]+size[x]-1);
  }
} tree;
// tree.init(n) -> add_edge(a,b) -> build(root)
// O((logn)^2)
// update(x, y, z) -> modify path from x to y
// query(x, y) -> query path from x to y
// O(logn)
// pure_update(x,z) -> modify x subtree
// pure_query(x) -> query x subtree