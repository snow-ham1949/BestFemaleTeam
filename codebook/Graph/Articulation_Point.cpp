const int mxn = 2e4 + 5;

vector<int> g[mxn];
int cnt = 0, ap_num = 0;
int dfn[mxn], low[mxn], vis[mxn], is_ap[mxn];

void tarjan(int u, int fa)
{
  vis[u] = 1;
  low[u] = dfn[u] = ++cnt;
  int child = 0;
  for (int v : g[u])
  {
    if (!vis[v]) {
      child++;
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
      if (fa != -1 && low[v] >= dfn[u] and !is_ap[u]) {
        is_ap[u] = 1;
        ap_num++;
      }
    }
    else if (v != fa){
      low[u] = min(low[u], dfn[v]);
    }
  }

  if (fa == -1 && child > 1 && !is_ap[u]) {
    is_ap[u] = 1;
    ap_num++;
  }
}

void solve()
{
  for (int i = 1; i <= n; i++)
  {
    if (!vis[i]) {
      tarjan(i, -1);
    }
  }
}
