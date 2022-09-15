// range sum queries
// 1-based
struct Seg{

  static const int mxn = 2e5 + 5;

  struct Node {
    ll data, tag;
  } seg[4 * mxn];

  ll a[mxn];

  ll get_val(int l, int r, int id) {
    return (r - l + 1) * seg[id].tag + seg[id].data;
  }

  void push(int l, int r, int id) {
    seg[id].data = get_val(l, r, id);
    seg[id * 2].tag += seg[id].tag;
    seg[id * 2 + 1].tag += seg[id].tag;
    seg[id].tag = 0;
  }

  void pull(int l, int r, int id) {
    int m = (l + r) >> 1;
    seg[id].data = get_val(l, m, id * 2) + get_val(m + 1, r, id * 2 + 1);
  }

  void build(int l, int r, int id = 1) {
    if (l == r) {
      seg[id].data = a[l];
      return;
    }
    int m = (l + r) >> 1;
    build(l, m, id * 2);
    build(m + 1, r, id * 2 + 1);
    pull(l, r, id);
  }

  ll query(int ql, int qr, int l, int r, int id = 1) {
    if (qr < l || r < ql) return 0ll;
    if (ql <= l && r <= qr) return get_val(l, r, id);
    push(l, r, id);
    int m = (l + r) >> 1;
    return query(ql, qr, l, m, id * 2) + query(ql, qr, m + 1, r, id * 2 + 1);
  }

  void update(int ql, int qr, ll v, int l, int r, int id = 1) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
      seg[id].tag += (v - seg[id].data);
      return;
    }
    push(l, r, id);
    int m = (l + r) >> 1;
    update(ql, qr, v, l, m, id * 2);
    update(ql, qr, v, m + 1, r, id * 2 + 1);
    pull(l, r, id);
  }
} seg;


