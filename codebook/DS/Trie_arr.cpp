int trie[MAXN][65] = {{0}}, EndOfWord[MAXN]={0}, id = 0;

int getindex(char a){
  return a - 'a';
}

void insert(string s){
  int rt = 0, len = s.length();
  for(int i = 0; i < len; i++){
    int index = getindex(s[i]);
    if(!trie[rt][index]){
      id ++;
      trie[rt][index] = id;
    }
    rt = trie[rt][index];
  }
  EndOfWord[rt] ++;
}

bool find(string s){
  int rt = 0, len = s.length();
  for(int i = 0; i < len; i++){
    int index = getindex(s[i]);
    if(!trie[rt][index]) return false;
    rt = trie[rt][index];
  }
  if(!EndOfWord[rt]) return false;
  return true;
}