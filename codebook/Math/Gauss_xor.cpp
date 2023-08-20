int a[N][N];
void Gauss(int n) {
  int c, r;
  for (c = 0, r = 0; c < n; c++) {
    int t = r;
    for (int i = r; i < n; i++) {
      if (a[i][c]) {
        t = i;
        break;
      }
    }
    if (!a[t][c]) continue;
    for (int i = c; i <= n; i++) swap(a[r][i], a[t][i]);
    for (int i = r + 1; i < n; i++)
      if (a[i][c])
        for (int j = n; j >= c; j--) a[i][j] ^= a[r][j];
    r++;
  }
  if (r < n) {
    for (int i = r; i < n; i++) {
      if (a[i][n]) {
        return -1; // no solution
      }
    }
    return 1; // infinite solution
  }
  for (int i = n - 1; i >= 0; i--)
    for (int j = i + 1; j < n; j++)
      a[i][n] ^= a[i][j] * a[j][n];
  return 0; // only on solution
}

//usage: 
//for i in [0, n):
//  for j in [0, n]:
//    cin >> a[i][j];
//int res = Gauss(n);
//result in a[0..n - 1][n]
