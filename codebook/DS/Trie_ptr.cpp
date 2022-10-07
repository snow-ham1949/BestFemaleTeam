struct Node{
  Node *child[CSIZE]={0};
  int EndOfWord = 0;
  string str;

  int getindex(char a){
    return a-'a';
  }

  void insert(string s){
    Node *tmp = this;
    int len = s.length();
    for (int i = 0; i < len; i++)
    {
        int index = getindex(s[i]);
        if (!tmp->child[index])
            tmp->child[index] = new Node;
        tmp = tmp->child[index];
    }
    tmp->EndOfWord ++;
    tmp->str = s;
  }

  int find(string s){
    Node *tmp = this;
    int len = s.length();
    for(int i = 0; i < len; i++){
      int index = getindex(s[i]);
      if(!tmp->child[index]) return 0;
      tmp = tmp->child[index];
    }
    return tmp->EndOfWord;
  }
};
