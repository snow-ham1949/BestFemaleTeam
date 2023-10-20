vector<pii> edges[MAXN];
// edges[i]: edge(i, edges[i].second) with weight edges[i].first
// O(ElogV)
int Prim_MST(int N){
  bool choose[N] = {0};
  int count = 0, weight = 0;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  // choose one vertex
  choose[0] = 1;
  count ++;
  // push its edges to pq
  for(auto it : edges[0]){
    pq.push(it);
  }
  // do it until pq empty
  while(!pq.empty()){
    auto add = pq.top();
    pq.pop();
    if(choose[add.second])
      continue;
    choose[add.second] = 1;
    //printf("add: vertex %d, with %d\n", add.second, add.first);
    count ++;
    weight += add.first;
    for(auto it : edges[add.second]){
      pq.push(it);
    }
  }
  if(count != N) return -1;
  return weight;
}
