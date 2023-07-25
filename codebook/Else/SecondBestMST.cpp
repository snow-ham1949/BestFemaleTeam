const int MAXN = 1e5 + 10;
const int MAXM = 3e5 + 10;
const int MAXD = ceil(log2(MAXN));
const ll INF = (1ll << 62);

struct Edge {
  int u, v, w;
  // u->v
  bool operator < (const Edge &rhs) const {
    return w < rhs.w;
  }
} E[MAXM];

int N, M, fa[MAXN], vis[MAXM]; //vis: is in MST
vector<pii> v[MAXN];
int an[MAXN][MAXD], mx[MAXN][MAXD], me[MAXN][MAXD], d[MAXN];
ll sum;
int find(int x) {
  return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
}
void Kruskal() { //1-base
  sort(E + 1, E + M + 1);
  int total = 0;
  for (int i = 1; i <= M; i++) {
    int x = E[i].u, y = E[i].v, fx = find(x), fy = find(y);
    if(x == y) continue;
    if (fx != fy) {
      fa[fx] = fy; 
      total++, sum += E[i].w, vis[i] = 1;
      v[x].push_back(make_pair(y, E[i].w));
      v[y].push_back(make_pair(x, E[i].w)); 
    }
    if (total == N - 1) break;
  }
}

void dfs(int x, int p) {
  d[x] = d[p] + 1; an[x][0] = p; 
  for(int i = 0, to; i < SZ(v[x]); i++) {
    if((to = v[x][i].X) == p) continue;
    mx[to][0] = v[x][i].Y;
    dfs(to, x);
  }
}

void pre() {
  for (int i = 1; i <= MAXD-1; i++) {
    for (int j = 1; j <= N; j++) {
      an[j][i] = an[an[j][i - 1]][i - 1];
      int topf = an[j][i - 1]; // 2^i-1 ancestor
      mx[j][i] = max(mx[j][i - 1], mx[topf][i - 1]);
      me[j][i] = max(me[j][i - 1], me[topf][i - 1]);
      if (mx[j][i - 1] > mx[topf][i - 1]) me[j][i] = max(me[j][i], mx[topf][i - 1]);
      else if (mx[j][i - 1] < mx[topf][i - 1]) me[j][i] = max(me[j][i], mx[j][i - 1]);
    }
  }
}

int LCA(int x, int y) {
  if (d[x] < d[y]) swap(x, y);
  for (int i = MAXD-1; i >= 0; i--) if (d[an[x][i]] >= d[y]) x = an[x][i];
  if (x == y) return x;
  for (int i = MAXD-1; i >= 0; i--) if (an[x][i] != an[y][i]) x = an[x][i], y = an[y][i];
  return an[x][0];
}

int findmax(int x, int lca, int val) {
  ll ans = 0;
  for (int i = MAXD-1; i >= 0; i--) {
    if (d[an[x][i]] >= d[lca]) {
      // if (mx[x][i] == val) ans = max(ans, (ll) me[x][i]);
      // else 
      ans = max(ans, (ll) mx[x][i]);
      x = an[x][i];
    }
  }
  return ans;
}

void work() {
  ll ans = INF;
  for (int i = 1; i <= M; i++) {
    if (vis[i]) continue;
    int x = E[i].u, y = E[i].v, z = E[i].w;
    if(x == y) continue;
    int lca = LCA(x, y);
    int lmx = findmax(x, lca, z), rmx = findmax(y, lca, z);
    // if (max(lmx, rmx) != z)  
    ans = min(ans, sum + z - max(lmx, rmx));
  }
  cout << ans << endl;
}

void init(){
  for(int i = 1; i <= N; i++){
    fa[i] = i;
    v[i].clear();
  }
  // memset(E, 0, sizeof(E));
  memset(vis, 0, sizeof(vis));
  memset(an, 0, sizeof(an));
  memset(mx, 0, sizeof(mx));
  memset(me, 0, sizeof(me));
  memset(d, 0, sizeof(d));
  sum = 0;
}

void add_edge(int i, int x, int y, int z){
  E[i] = (Edge) {x, y, z};
}

void solver(){
  Kruskal();
  dfs(1, 0);
  pre();
  work();
}
// O(M log N)
// init -> add_edge -> solver
