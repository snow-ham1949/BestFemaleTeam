struct Node{
  Node *child[CSIZE]={0};
  int EndOfWord = 0;
};

int getindex(char a){
  return a-'a';
}

void insert(Node *T, string s){
  Node *tmp = T;
  int len = s.length();
  for (int i = 0; i < len; i++)
  {
      int index = getindex(s[i]);
      if (!tmp->child[index])
          tmp->child[index] = new Node;
      tmp = tmp->child[index];
  }
  tmp->EndOfWord ++;
}

bool find(Node *T, string s){
  Node *tmp = T;
  int len = s.length();
  for(int i = 0; i < len; i++){
    int index = getindex(s[i]);
    if(!tmp->child[index]) return false;
    tmp = tmp->child[index];
  }
  if(!tmp->EndOfWord) return false;
  return true;
}
