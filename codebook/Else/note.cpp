articulation point & bridge: if deleted, then connected component ++
tree centroid: if deleted, then T will be separated into multiple trees, where nodes of each <= n / 2
min cut: 
  1. a cut such that all nodes can be separated into two sets S, T = V - S, and the capacity is minimum
  2. how to find
     do flow
     block cap = 0 edge
     bfs from s, can reach -> S, can't reach -> T

