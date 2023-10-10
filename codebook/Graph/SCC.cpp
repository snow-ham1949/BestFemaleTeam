struct SCC {
  vector<int> g[N];
	vector<int> comp, ind;
  stack<int> sta;
	int di = 0; // DFS counter
	int cc = 0; // Comp count

  void add_edge(int s, int e) {
    g[s].push_back(e);
  }
	int dfs(int i) {
		if (ind[i] != -1) return (comp[i] == -1) ? ind[i] : di;
		ind[i] = di;
		int md = di;
		++di;
	
		sta.push(i);
		for (auto t : g[i]) md = min(md, dfs(t));
	
		if (md == ind[i]) {
			while(comp[i] == -1) {
				comp[sta.top()] = cc;
				sta.pop();
			}
			++cc;
		}
		return md;
	}
  void get() {
    for (int i = 0; i < N; i++) dfs(i);
  }
  SCC() {
    comp.assign(N, -1);
    ind.assign(N, -1);
  }
};
