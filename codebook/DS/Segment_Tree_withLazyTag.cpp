template<typename T>
struct Seg {
  struct Node {
    T val;
    T lzAdd;
    T lzSet;

    Node() : val(0), lzAdd(0), lzSet(0) {}
  };

  vector<Node> tree;
  int maxN;

#define lc p << 1
#define rc p << 1 | 1

  void pushup(int p) {
    tree[p].val = tree[lc].val + tree[rc].val;
  }

  void pushdown(int p, int l, int mid, int r) {
    if (tree[p].lzSet != 0) {
      tree[lc].lzSet = tree[rc].lzSet = tree[p].lzSet;
      tree[lc].val = (mid - l + 1) * tree[p].lzSet;
      tree[rc].val = (r - mid) * tree[p].lzSet;
      tree[lc].lzAdd = tree[rc].lzAdd = 0;
      tree[p].lzSet = 0;
    } else if (tree[p].lzAdd != 0) {  
      if (tree[lc].lzSet == 0) tree[lc].lzAdd += tree[p].lzAdd;
      else {
        tree[lc].lzSet += tree[p].lzAdd;
        tree[lc].lzAdd = 0;
      }
      if (tree[rc].lzSet == 0) tree[rc].lzAdd += tree[p].lzAdd;
      else {
        tree[rc].lzSet += tree[p].lzAdd;
        tree[rc].lzAdd = 0;
      }
      tree[lc].val += (mid - l + 1) * tree[p].lzAdd;
      tree[rc].val += (r - mid) * tree[p].lzAdd;
      tree[p].lzAdd = 0;
    }
  }

  Seg(int maxN) : maxN(maxN) {
    tree.resize(maxN << 2);
  }

  void build(const vector<T>& arr, int p, int l, int r) {
    tree[p].lzAdd = tree[p].lzSet = 0;
    if (l == r) {
      tree[p].val = arr[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(arr, lc, l, mid);
    build(arr, rc, mid + 1, r);
    pushup(p);
  }

  void add(int p, int l, int r, int a, int b, T val) {
    if (a > r || b < l) return;
    if (a <= l && r <= b) {
      tree[p].val += (r - l + 1) * val;
      if (tree[p].lzSet == 0) tree[p].lzAdd += val;
      else tree[p].lzSet += val;
      return;
    }
    int mid = (l + r) >> 1;
    pushdown(p, l, mid, r);
    add(lc, l, mid, a, b, val);
    add(rc, mid + 1, r, a, b, val);
    pushup(p);
  }

  void set(int p, int l, int r, int a, int b, T val) {
    if (a > r || b < l) return;
    if (a <= l && r <= b) {
      tree[p].val = (r - l + 1) * val;
      tree[p].lzAdd = 0;
      tree[p].lzSet = val;
      return;
    }
    int mid = (l + r) >> 1;
    pushdown(p, l, mid, r);
    set(lc, l, mid, a, b, val);
    set(rc, mid + 1, r, a, b, val);
    pushup(p);
  }

  T query(int p, int l, int r, int a, int b) {
    if (a > r || b < l) return 0;
    if (a <= l && r <= b) return tree[p].val;
    int mid = (l + r) >> 1;
    pushdown(p, l, mid, r);
    return query(lc, l, mid, a, b) + query(rc, mid + 1, r, a, b);
  }
};

// usage: Seg<ll> seg(n);
// build: seg.build(vector, 1, 1, n);
// vector should be 1-based
// add: increase [a, b] by x
// set: set [a, b] to x
// query: sum of [a, b]
