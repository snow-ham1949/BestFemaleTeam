const int MAXN = 500010;
const int MAXD = ceil(log2(MAXN));
struct LCA{ //1-base
  vector<int> G[MAXN];
  int n;
  int d[MAXN], lg[MAXN];
  int an[MAXN][MAXD];

  void init(int _n){
    n = _n;
    for(int i = 0; i <= n; i++){
      G[i].clear();
    }
    memset(d,0,sizeof(d));
    memset(lg,0,sizeof(lg));
    memset(an,-1,sizeof(an));
    // precompute
    lg[1] = 0;
    for (int i = 2; i < MAXN; ++i) 
      lg[i] = lg[i / 2] + 1;
  }

  void add_edge(int u, int v){
    G[u].push_back(v);
    G[v].push_back(u);
  }

  void dfs(int u, int p = -1, int depth = 0) {
    d[u] = depth;
    an[u][0] = p;
    for (int i = 1; i <= lg[n - 1] && an[u][i - 1] != -1; ++i)
      an[u][i] = an[an[u][i - 1]][i - 1]; 
      // 2^i = 2^(i-1) + 2^(i-1)      
    for (auto& v : G[u]) {
      if (v == p) continue; // parent
      dfs(v, u, depth + 1);
    }
  }

  int query(int u, int v) {
    if (d[u] > d[v]) swap(u, v);
    for (int i = lg[d[v] - d[u]]; i >= 0; --i)
      if (d[v] - d[u] >= (1 << i)) 
        v = an[v][i];
    // v move to same depth
    if (u == v) return u;

    for (int i = lg[d[u]]; i >= 0; --i)
      if (an[u][i] != an[v][i]) 
        u = an[u][i], v = an[v][i];

    // lca(u,v)
    return an[u][0];
  }
};
// build O(VlogV), query O(logV)
// init -> add_edge -> dfs(root) -> query
LCA tree;
