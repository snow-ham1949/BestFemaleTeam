const int mxn = 1e5 + 5;
vector<int> g[mxn];
int in[mxn]; // indegree

vector<int> tpsort()
{
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 1; i <= n; i++) 
  {
    if (in[i] == 0) pq.push(i);
  }
  
  vector<int> vec;
  while (!pq.empty())
  {
    int u = pq.top(); pq.pop();
    vec.emplace_back(u);
    for (auto v : g[u])
    {
      --in[v];
      if (in[v] == 0) pq.push(v);
    }
  }

  return vec;
}

