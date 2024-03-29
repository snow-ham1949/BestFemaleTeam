using Vi = vector<int>;
#define pb push_back
#define each(a, x) for (auto &a: (x))
struct SAT2 : Vi {
  vector<Vi> G;
  Vi order, flags;

  // Init n variables, you can add more later
  SAT2(int n = 0) : G(n * 2) {}

  // Add new var and return its index
  int addVar() {
    G.resize(SZ(G) + 2); return SZ(G)/2;
  }

  // Add (i => j) constraint
  void imply(int i, int j) {
    i = max(i * 2 - 1, -i * 2 -2);
    j = max(j * 2 - 1, -j * 2 - 2);
    G[i].pb(j); G[j ^ 1].pb(i ^ 1);
  }

  // Add (i v j) constraint
  void either(int i, int j) { imply(-i, j); }

  // Add !(i ∧ j) constraint
  void notBoth(int i, int j) { imply(i, -j); }

  // Constraint at most one true variable
  void atMostOne(Vi& vars) {
    int x = addVar();
    each(i, vars) {
      int y = addVar();
      imply(x, y); imply(i, -x); imply(i, y);
      x = y;
    }
  }

  // Solve and save assignments in `values`
  bool solve() { // O(n+m), Kosaraju is used
    assign(SZ(G)/2+1, -1);
    flags.assign(SZ(G), 0);
    for (int i = 0; i < SZ(G); i++) dfs(i);
    while (!order.empty()) {
      if (!propag(order.back()^1, 1)) return 0;
      order.pop_back();
    }
    return 1;
  }

  void dfs(int i) {
    if (flags[i]) return;
    flags[i] = 1;
    each(e, G[i]) dfs(e);
    order.pb(i);
  }

  bool propag(int i, bool first) {
    if (!flags[i]) return 1;
    flags[i] = 0;
    if (at(i/2+1) >= 0) return first;
    at(i/2+1) = i&1;
    each(e, G[i]) if (!propag(e, 0)) return 0;
    return 1;
  }
};

