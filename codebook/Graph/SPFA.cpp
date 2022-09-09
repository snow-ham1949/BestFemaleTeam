const int mxn = 10000 + 5;

bitset<mxn> inque;
vector<pii> g[mxn];
queue<int> q;
vector<ll> dis(mxn, (1ll << 31) - 1);
vector<ll> cnt(mxn, 0);

bool SPFA(int st) {
  q.emplace(st);
  dis[st] = 0;
  
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    inque[u] = 0;
    for (auto [v, w] : g[u])
    {
      if (dis[v] > dis[u] + w) {
        if (++cnt[v] >= n) return false; // contains negative cycle
        dis[v] = dis[u] + w;

        if (!inque[v]) {
          inque[v] = 1;
          q.emplace(v);
        }
      }
    }
  }

  return true;
}

