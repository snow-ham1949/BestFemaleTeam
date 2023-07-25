struct Node {
  ll val, lzAdd, lzSet;

  Node() : val(0), lzAdd(0), lzSet(0) {}
};

vector<Node> tree;
int n;

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

void build(const vector<ll>& arr, int p = 1, int l = 1, int r = n) {
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

void add(ll val, int a, int b, int p = 1, int l = 1, int r = n) {
  if (a > r || b < l) return;
  if (a <= l && r <= b) {
    tree[p].val += (r - l + 1) * val;
    if (tree[p].lzSet == 0) tree[p].lzAdd += val;
    else tree[p].lzSet += val;
    return;
  }
  int mid = (l + r) >> 1;
  pushdown(p, l, mid, r);
  add(val, a, b, lc, l, mid);
  add(val, a, b, rc, mid + 1, r);
  pushup(p);
}

void _set(ll val, int a, int b, int p = 1, int l = 1, int r = n) {
  if (a > r || b < l) return;
  if (a <= l && r <= b) {
    tree[p].val = (r - l + 1) * val;
    tree[p].lzAdd = 0;
    tree[p].lzSet = val;
    return;
  }
  int mid = (l + r) >> 1;
  pushdown(p, l, mid, r);
  _set(val, a, b, lc, l, mid);
  _set(val, a, b, rc, mid + 1, r);
  pushup(p);
}

ll query(int a, int b, int p = 1, int l = 1, int r = n) {
  if (a > r || b < l) return 0;
  if (a <= l && r <= b) return tree[p].val;
  int mid = (l + r) >> 1;
  pushdown(p, l, mid, r);
  return query(a, b, lc, l, mid) + query(a, b, rc, mid + 1, r);
}

// usage
// build: tree.resize(n << 2); build(vector);
// vector should be 1-based
// add: increase [a, b] by x -> add(x, a, b);
// set: set [a, b] to x -> _set(x, a, b);
// query: sum of [a, b] -> query(a, b);
