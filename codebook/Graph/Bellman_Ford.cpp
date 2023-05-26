const ll inf = 1e18;
const int N = 2500 + 5;
int par[N];
ll dist[N];

struct Edge {
  int u, v, w;
};

vector<Edge> edges;

vector<int> Bellman_Ford(int n) {
  for (int i = 1; i <= n; i++) {
    par[i] = -1;
    dist[i] = inf;
  }
  dist[1] = 0ll;
  int x = -1;
  for (int i = 1; i <= n; i++) {
    x = -1;
    for (Edge e : edges) {
      if (dist[e.v] > dist[e.u] + (ll)e.w) {
        dist[e.v] = max(-inf, dist[e.u] + (ll)e.w);
        par[e.v] = e.u;
        x = e.v;
      }
    }
  }
  if (x == -1) return vector<int>();

  for (int i = 1; i <= n; i++)  x = par[x];
  vector<int> cycle;
  for (int u = x;; u = par[u]) {
    cycle.push_back(u);
    if (u == x && SZ(cycle) > 1) break;
  }
  reverse(cycle.begin(), cycle.end());
  return cycle;
}