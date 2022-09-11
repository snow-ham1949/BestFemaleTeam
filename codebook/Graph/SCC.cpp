const int mxn = 1e5 + 5;

vector<int> g[mxn], new_g[mxn];
int dfn[mxn], low[mxn], in_stk[mxn], root[mxn];
int num_SCC, cnt;
stack<int> stk;
vector<int> root_nodes;

#define eb emplace_back
void tarjan(int u, int fa)
{ 
  // fa: father, for debugging
  dfn[u] = low[u] = ++cnt;
  stk.push(u);
  in_stk[u] = 1;

  for (int v : g[u])
  {
    if (!dfn[v]) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
    } else if (in_stk[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }

  if (dfn[u] == low[u]) {
    root_nodes.eb(u);
    int x;
    do {
      x = stk.top();
      stk.pop();
      root[x] = u;
      in_stk[x] = 0;
    } while (x != u);
    num_SCC++;
  }
}

void solve()
{
  for (int i = 1; i <= n; i++) 
  {
    if (!dfn[i]) tarjan(i, i);
  }

  for (int u = 1; u <= n; u++)
  {
    for (int v : g[u])
    {
      if (root[v] != root[u]) {
        new_g[root[u]].eb(root[v]);
      }
    }
  }
}

