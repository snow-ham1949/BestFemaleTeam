// point update, range query
// range update, point query: 差分
// range update, range query: 要用兩個 BIT，一個維護差分D_i, 一個維護差分D_i * i

template <class T>
struct BIT {
  int n;
  vector<T> bit;
  BIT(int _n): n(_n) {
    bit.assign(n, 0);
  }
  T sum(int x) {
    T res = 0;
    for (; x; x -= x & (-x)) res += bit[x];
    return res;
  }
  T sum(int l, int r) {
    return sum(r) - sum(l - 1);
  }
  void add(int x, T val) { // add val, not = val !
    for (; x <= n; x += x & (-x)) bit[x] += val;
  }
};
// 0 - based -> BIT bit(n);
// 1 - based -> BIT bit(n + 1);
