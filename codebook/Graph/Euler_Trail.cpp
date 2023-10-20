// del[now] : G[now][1,2……,del[now]-1] are visited
// start from G[now][del[now]]
int del[MAXN] = {0};
// in-degree, out-degree
// in, out degree are calculated when add edges
int in[MAXN] = {0}, out[MAXN] = {0}; 
stack <int> st;
// G[i] is sorted, represent directed graph
vector <int> G[MAXN];

void dfs(int now)
{
	for(int i=del[now];i<G[now].size();i=del[now])
	{ 
		del[now]=i+1;
		dfs(G[now][i]);
	}
	st.push(now);
}

void Euler_Path(int N){
  // if euler circuit exists
  // start from first vertex
  int S = 1, T, cnt[2] ={0};
  // in == out
  bool flag = true;
  for(int i = 1; i <= N; i++){
    if(in[i] != out[i]) flag=false;
    if(out[i] - in[i] == 1) cnt[0]++, S=i; // start
    if(in[i] - out[i] == 1) cnt[1]++, T=i; // terminate
  }
  // if needed, we need to check whether there's 
  // a path from S to T
  if(!flag && !(cnt[0] == 1 && cnt[1] == 1)){
    printf("No"); 
    return;
  }
  dfs(S);
  while(!st.empty()) printf("%d ",st.top()),st.pop();
  return; 
}
