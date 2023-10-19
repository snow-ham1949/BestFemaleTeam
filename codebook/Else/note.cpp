1. articulation point & bridge
  if deleted, then connected component ++
2. tree centroid
  if deleted, then T will be separated into multiple trees, where nodes of each <= n / 2
3. min cut: 
   - a cut such that all nodes can be separated into two sets S, T = V - S, and the capacity is minimum
   - how to find
     do flow
     block cap = 0 edge
     bfs from s, can reach -> S, can't reach -> T
4. bipartite matching using dinic
  - after doing dinic.maxflow
  - for (int i = 1; i <= m; i++) {
      for (auto [to, rev, flow, cap] : dinic.G[i]) {
        if (flow == 1) cout << i << " " << to << "\n";
      }
    }
