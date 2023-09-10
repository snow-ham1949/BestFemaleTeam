// find x of Ax = B 
typedef unsigned int ui;
typedef unsigned long long ull;
const ui M = 998244353;

ui mypw(ui x, int y) {
  ui res = 1;
  while (y) {
    if (y & 1) res = (ull)res * x % M;
    x = (ull)x * x % M;
    y >>= 1;
  }
  return res;
}

tuple<int, vector<ui>, vector<vector<ui>>> gauss(vector<vector<ui>> &a) { // {rank, one of the solution, basis}
	int n = SZ(a), m = SZ(a[0])-1, i, j, k, R=m;
	vector<int> fix(m, -1);
	for (i = k = 0; i < m; i++) {
		for (j = k; j < n; j++) if (a[j][i]) break;
		if (j == n) continue;
		fix[i] = k; --R;
		swap(a[k],a[j]);
		ui *u = a[k].data();
		ui x = mypw(u[i], M - 2);
		for (j = i; j <= m; j++) u[j] = (ull)u[j] * x % M;
		for (auto &v:a) if (v.data() != a[k].data())
		{
			x = M - v[i];
			for (j = i; j <= m; j++) v[j] = (v[j] + (ull) x * u[j]) % M;
		}
		++k;
	}
	for (i = k; i < n; i++) if (a[i][m]) return {-1, {}, {}};
	vector<ui> r(m);
	vector<vector<ui>> c;
	for (i = 0; i < m; i++) if (fix[i] != -1) r[i]=a[fix[i]][m];
	for (i = 0; i < m; i++) if (fix[i] == -1)
	{
		vector<ui> r(m);
		r[i] = 1;
		for (j = 0; j < m; j++) if (fix[j] != -1) r[j] = (M - a[fix[j]][i]) % M;
		c.push_back(r);
	}
	return {R, r, c};
}

/* 
usage:
vector<vector<ui>> a(n, vector<ui>(m, 0u));
for (auto &v : a) { // A
  for (auto &x : v) cin >> x;
}
for (auto &v : a) { // B
  int x; cin >> x;
  v.push_back(x);
}
*/
