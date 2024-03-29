// logn = ceil(log2(mxn))
int st[mxn][logn]; // sparse table, store answer for [i, i + 2^j - 1]
int a[mxn]; // array
int lg[mxn]; // log value
int n;

void init()
{
	for (int i = 0; i < n; i++) cin >> st[i][0];
	for (int j = 1; j < logn; j++) {
		for (int i = 0; i + (1 << j) <= n; i++){
			st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}
}
/*
	cin >> n;
	init();
	int l, r; // 1-based
	cin >> l >> r;
	l--, r--;
	int j = __lg(r - l + 1); -> min(st[l][j], st[r - (1 << j) + 1][j])
*/


