double a[N][N], x[N];
const double eps=1e-6;
int solve(int n, int m){
  int c=0;
  int r;
  for(r = 0; r < n && c < m; r++, c++) {
    int maxr = r;
    for(int i = r + 1; i < n; i++) {
      if(abs(a[i][c]) > abs(a[maxr][c]))
        maxr = i;
    }
    if(maxr != r) swap(a[r], a[maxr]);
    if(fabs(a[r][c]) <eps){
      r--;
      continue;
    }
    for(int i = r + 1; i < n; i++){
      if(fabs(a[i][c]) > eps){
        double k = a[i][c] / a[r][c];
        for(int j = c; j < m + 1; j++) a[i][j] -= a[r][j] * k;
        a[i][c] = 0;
      }
    }
  } 
  for(int i = r; i < m; i++){
    if(fabs(a[i][c]) > eps) return -1; // no solution
  }    
  if(r < m) return 1; // infinite solution
  for(int i = m - 1; i >= 0; i--){
      for(int j = i + 1; j < m; j++) a[i][m] -= a[i][j] * x[j];
      x[i] = a[i][m] / a[i][i];
  }
  return 0; // only one solution
}

// usage: 
// for i in [0, n) : 
//  for j in [0, n] :
//    cin >> a[i][j];
// int res = solve(n, n);
// result in x[0..n - 1]
