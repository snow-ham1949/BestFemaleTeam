struct Bipartite_Matching { // 0-base
  int l, r;
  int mp[MAXN], mq[MAXN]; // i -> mp[i], mq[i] -> i
  int dis[MAXN], cur[MAXN];

  vector<int> G[MAXN], G1[MAXN];
  void init(int _l, int _r){
    l = _l, r = _r;
    for(int i = 0; i < l; ++i){
      G[i].clear();
    }
    /* only use in vertex cover
    for(int j = 0; j < r; ++j){
      G1[j].clear();
    }
    */
  }
  void add_edge(int s, int t){
    G[s].push_back(t);
    G1[t].push_back(s);
  }
  bool dfs(int u){
    for(int &i = cur[u]; i < SZ(G[u]); ++i){
      int e = G[u][i];
      if(mq[e] == -1 || (dis[mq[e]] == dis[u] + 1 && dfs(mq[e]))){
        mp[u] = e, mq[e] = u;
        return 1;
      }
    }
    dis[u] = -1;
    return 0;
  }
  bool bfs(){
    int rt = 0;
    queue<int> q;
    fill_n(dis, l, -1);
    for(int i = 0; i < l; ++i)
      if (mp[i] == -1)
        q.push(i), dis[i] = 0;
    while (!q.empty()){
      int u = q.front();
      q.pop();
      for(int e : G[u]){
        if(mq[e] == -1)
          rt = 1;
        else if (dis[mq[e]] == -1){
          q.push(mq[e]);
          dis[mq[e]] = dis[u] + 1;
        }
      }
    }
    return rt;
  }
  int matching(){
    int rt = 0;
    fill_n(mp, l, -1);
    fill_n(mq, r, -1);
    while(bfs()){
      fill_n(cur, l, 0);
      for(int i = 0; i < l; ++i){
        if(mp[i] == -1 && dfs(i))
          ++ rt;
      }
    }
    return rt;
  }

  /* only use for vertex cover
  // 0: left, 1: right
  int type[2][MAXN];
  // 0: never in cover set
  // -1: maybe in the cover set (point with perfect matching, not visited in dfs)
  // 1: must be in the cover set
  void dfs2(int u, int right){
    if(type[right][u] != -1) return;
    type[right][u] = 0;
    if(right){
      for(auto v : G1[u]){
        type[!right][v] = 1;
        if(mp[v] != u) dfs2(mp[v], right);
      } 
    } else {
      for(auto v : G[u]){
        type[!right][v] = 1;
        if(mq[v] != u) dfs2(mq[v], right);
      } 
    }
  }

  void vertex_cover(){
    //NOTE: make sure to run matching first
    fill_n(type[0], l, -1);
    fill_n(type[1], r, -1);
    // run dfs2 on left
    for(int i = 0; i < l; i++){
      if(mp[i] == -1){
        dfs2(i, 0);
      }
    }
    // run dfs2 on right
    for(int i = 0; i < r; i++){
      if(mq[i] == -1){
        dfs2(i, 1);
      }
    }
  }
  */
};
// O(VE)
// init -> add_edge -> matching
// vertex coverset number = matching number
// vertex coverset -> after matching -> vertex_cover
// independent set number = minimum path cover number = V - matching number
// independent set -> after vertex_cover (return M) -> independent set is V\M
