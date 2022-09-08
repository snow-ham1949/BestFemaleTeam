vector<pii> g[mxn];
vector<ll> dis(mxn, 1e18);

// does not work for graph existing negative weight
void dijkstra(int st)
{
  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.emplace(0ll, st);
  dis[st] = 0;

  while (!pq.empty())
  {
    auto [du, u] = pq.top(); pq.pop();
    if (dis[u] != du) continue;

    for (auto &[v, w] : g[u])
    {
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        pq.emplace(dis[v], v);
      }
    }
  }
}