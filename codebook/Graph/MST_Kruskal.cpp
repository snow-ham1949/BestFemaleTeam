// edge[i] = {z, x, y}
// edge(x, y) with weight z
vector<vector<int>> edgelist;

int Kruskal_MST(int N){
  int set_count = N, weight = 0;
  // make set for all vertex
  disjoint_set *pointset[N];
  for(int i = 0; i < N; i++)
    pointset[i] = make_set(i);
  // sort edges
  sort(edgelist.begin(), edgelist.end());
  // start union  
  for(auto it : edgelist){
    // if in different set, then union
    if(find_set(pointset[it[1]]) != find_set(pointset[it[2]])){
      Union(pointset[it[1]], pointset[it[2]]);
      set_count --;
      weight += it[0];
    }
  }
  if(set_count != 1) return -1;
  return weight;
}