int Node[MAXN][CSIZE] = {{0}}, EndOfWord[MAXN]={0}, id_of_str[MAXN] = {0}, failptr[MAXN] = {0};
int id = 0, que[MAXN]={0}, cnt[MAXN] = {0}, end_at[MAXN] = {0};

// usage
// ac.build(a); "a" contains patterns
// ac.find(t); t is the target text
// end_at[i]: a[i] ends at node end_at[i]
// cnt[end_at[i]]: a[i] appears cnt[end_at[i]] in t

int getindex(char a){
  return a - 'a';
}

void init(){
  memset(Node, 0, sizeof(Node));
  memset(EndOfWord, 0, sizeof(EndOfWord));
  memset(id_of_str, 0, sizeof(id_of_str));
  memset(failptr, -1, sizeof(failptr));
  memset(que, 0, sizeof(que));
  memset(cnt, 0, sizeof(cnt));
  id = 0;
}

void insert(string s, int id_){
  int rt = 0, len = s.length();
  for(int i = 0; i < len; i++){
    int index = getindex(s[i]);
    if(!Node[rt][index]){
      id ++;
      Node[rt][index] = id;
    }
    rt = Node[rt][index];
  }
  EndOfWord[rt] ++;
  id_of_str[rt] = id_;
  end_at[id_] = rt;
}

struct AC_Automaton{
  int root = 0;
  vector<string> patterns;

  void build(vector<string> patterns_){
    patterns = patterns_;
    int size = SZ(patterns);
    init();
    // build trie
    for(int i = 0; i < size; i++){
      insert(patterns[i], i);
    }

    // build failptr
    queue<int> q;
    int t = 0;
    // first layer's failptr is root
    for(int i = 0; i < CSIZE; i++){
      if(Node[root][i]){
        failptr[Node[root][i]] = root;
        q.push(Node[root][i]);
      }
    }

    // BFS
    while(!q.empty()){
      int x = q.front();
      q.pop();
      que[t++] = x;
      for(int i = 0; i < CSIZE; i++){
        if(Node[x][i]){
          q.push(Node[x][i]);
          int Fail = failptr[x];
          while(1){
            if(Fail == -1){
              // root
              failptr[Node[x][i]] = root;
              break;
            }

            if(Node[Fail][i]){
              failptr[Node[x][i]] = Node[Fail][i];
              break;
            } else {
              Fail = failptr[Fail];
            }
          }
        }
      }
    }
  }
  
  void find(string text){
    memset(cnt, 0, sizeof(cnt));
    int curr = root;
    int i = 0;
    int size = SZ(text);
    while(i < size){
      int index = getindex(text[i]);

      if(Node[curr][index]){
        curr = Node[curr][index];
        cnt[curr] ++;
        i++;
      } else {
        curr = failptr[curr];
        if(curr == -1){
          curr = root;
          cnt[curr] ++;
          i++;
        }
      }
    }
    for(int i = id - 1; i >= 0; i--){
      cnt[failptr[que[i]]] += cnt[que[i]];
    }
  }
};
