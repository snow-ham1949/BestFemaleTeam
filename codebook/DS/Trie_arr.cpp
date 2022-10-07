struct Node{
  int child[CSIZE] = {0};
  int EndOfWord = 0;
  string str;
} Node[MAXN];

int id = 0;
int getindex(char a){
  return a - 'a';
}

void insert(string s){
  int rt = 0, len = s.length();
  for(int i = 0; i < len; i++){
    int index = getindex(s[i]);
    if(!Node[rt].child[index]){
      id ++;
      Node[rt].child[index] = id;
    }
    rt = Node[rt].child[index];
  }
  Node[rt].EndOfWord ++;
  Node[rt].str = s;
}

bool find(string s){
  int rt = 0, len = s.length();
  for(int i = 0; i < len; i++){
    int index = getindex(s[i]);
    if(!Node[rt].child[index]) return false;
    rt = Node[rt].child[index];
  }
  if(!Node[rt].EndOfWord) return false;
  return true;
}
