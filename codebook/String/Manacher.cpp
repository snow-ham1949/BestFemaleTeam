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
