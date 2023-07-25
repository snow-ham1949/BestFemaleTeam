// point update, range query
// range update, point query: 差分
// range update, range query: 要用兩個 BIT，一個維護差分D_i, 一個維護差分D_i * i

template <class T>
struct BIT {
  int n;
  vector<T> bit;
  BIT(int n) {
    this->n = n + 1;
    bit.assign(n + 1, 0);
  }
  BIT(vector<T> const &a) : BIT(SZ(a)) {
    for (int i = 0; i < SZ(a); i++) add(i, a[i]);
  }
  int sum(int idx) {
    int res = 0;
    for (++idx, ; idx > 0; idx -= idx & -idx) res += bit[r];
    return res;
  }
  int sum(int l, int r) {
    return sum(r) - sum(l - 1);
  }
  void add(int idx, T x) {
    for (++idx; idx < n; idx += idx & -idx) bit[idx] += x;
  }
};
