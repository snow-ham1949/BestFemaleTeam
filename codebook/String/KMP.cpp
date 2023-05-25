// build pi function
// pi(i) is the length of the longest prefix of the substring s[0..i] which is also a suffix of this substring. 
vector<int> prefix_function(string s) {
    int n = SZ(s);
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

// find all pattern occurence starting index in text
vector<int> KMP(string text, string pat) {
  string s = pat + "#" + text;
  vector<int> pi = prefix_function(s);
  vector<int> res;
  int n = SZ(pat);
  for (int i = n + 1; i < SZ(s); i++) {
    if (pi[i] == n) {
      res.push_back(i - 2 * n);
    }
  }
  return res;
}
