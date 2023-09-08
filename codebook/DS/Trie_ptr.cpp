class Trie {
public:
  struct Node {
    bool end;
    Node *child[26];
    Node() {
        end = false;
        for (int i = 0; i < 26; i++) child[i] = NULL;
    }
  };
  Node *root;
  Trie() {
    root = new Node();
  }
  
  void insert(string word) {
    Node *node = root;
    for (char c : word) {
      int ind = c - 'a';
      if (node->child[ind] == NULL) node->child[ind] = new Node();
      node = node->child[ind];
    }
    node->end = true;
  }
  
  bool search(string word) {
    Node *node = root;
    for (char c : word) {
      int ind = c - 'a';
      if (node->child[ind] == NULL) return false;
      node = node->child[ind];
    }
    return node->end;
  }
  
  bool startsWith(string prefix) {
    Node *node = root;
    for (char c : prefix) {
      int ind = c - 'a';
      if (node->child[ind] == NULL) return false;
      node = node->child[ind];
    }
    return true;
  }
};
