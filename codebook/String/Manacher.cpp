// return length of longest palindrome in string tmp
// remember mxn should be at least 2 * string length
int d[mxn];
int Manacher(string tmp)
{
#define pb push_back
  string s = "&";
  int l = 0, r = 0, x = 0, ans = 0;
  for (char c : tmp) s.pb(c), s.pb('%');
  int sz = s.size();
  for (int i = 1; i < sz; i++)
  {
    d[i] = r > i ? min(d[2 * l - i], r - i) : 1;
    while (s[i + d[i]] == s[i - d[i]]) d[i]++;
    if (d[i] + i > r) r = i + d[i], l = i;
  }
  for (int i = 1; i < sz; i++)
  {
    if (s[i] == '%') x = max(x, d[i]);
  }
  ans = x / 2 * 2, x = 0;
  for (int i = 1; i < sz; i++)
  {
    if (s[i] != '%') x = max(x, d[i]);
  }
  return max(ans, (x - 1) / 2 * 2 + 1);
}

// return longest palindrome in string tmp
vector<int> manacherOdd(string s) {
  int n = SZ(s);
  s = "$" + s + "^";
  vector<int> p(n+2);
  int l = 1, r = 1;
  for (int i = 1; i <= n; i++) {
    p[i] = max(0, min(r - i, p[l + r - i]));
    while (s[i - p[i]] == s[i + p[i]]) p[i]++;
    if (i + p[i] > r) {
      l = i - p[i]; 
      r = i + p[i];
    }
  }
  return vector<int>(begin(p)+1,end(p)-1);
}
 
string manacher(string s) {
  string t;
  for(auto c : s) t += string("#") + c;
  vector<int> ans = manacherOdd(t + "#");
  int maxid = 1, maxlen = ans[1];
  for (int i = 1; i < SZ(ans) - 1; i++) {
    if (ans[i] > maxlen) { 
      maxlen = ans[i]; 
      maxid = i;
    }
  }
  return s.substr(maxid / 2 - (maxlen - 1) / 2, maxlen - 1);
}
