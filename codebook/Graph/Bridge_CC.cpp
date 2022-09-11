int bcc[MAXN], dic[MAXN], low[MAXN], component = 0, times = 1;
vector<int> Stack;

void init(){
    Stack.clear();
    memset(bcc,-1, sizeof(int) * MAXN);
    memset(dic,0, sizeof(int) * MAXN);
    memset(low,0, sizeof(int) * MAXN);
    component = 0;
    times = 1;
}

void tarjan(vector<int> *adj, int start, int parent){ 
    dic[start] = low[start] = times; times ++;
    Stack.push_back(start);
    for(auto v : adj[start]){
        if (dic[v] == 0)
          tarjan(adj,v, start);
        
        if (v != parent)
          low[start] = min(low[start], low[v]);
    }

    if(low[start] == dic[start]){
        int t = 0;
        do{
            t = Stack.back();
            bcc[t] = component;
            Stack.pop_back();
        }while(t != start);
        component ++;
    }
}

void findbcc(vector<int> *adj, int N){
  init();
  for(int i = 0; i < N; i++){
      if(dic[i] == 0)
          tarjan(adj, i, i);
  }
}

vector<int> build_bcc_graph(vector<int> *adj, int N){
  vector<int> adj_bcc[component];
  for(int l = 0; l < N; l++){
    for(auto j : adj[l]){
        int root1 = bcc[l], root2 = bcc[j];
        if(root1 != root2){
            adj_bcc[root1].push_back(root2);
            adj_bcc[root2].push_back(root1);
        }
    }            
  }
}