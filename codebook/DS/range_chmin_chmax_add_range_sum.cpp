const ll INF = 1e12;
ll a[maxN];
struct Node {
  ll sum;
  ll mx1, mx2, mxc;
  ll mn1, mn2, mnc;
  ll lazy;
  Node () {};
  Node (ll x) : sum(x), mx1(x), mx2(-INF), mn1(x), mn2(INF), mnc(1), mxc(1), lazy(0) {};
} st[maxN << 2];
void Merge(int id) {
  st[id].sum = st[id << 1].sum + st[id << 1 | 1].sum;
  if (st[id << 1].mx1 == st[id << 1 | 1].mx1) {
    st[id].mx1 = st[id << 1].mx1;
    st[id].mx2 = max(st[id << 1].mx2, st[id << 1 | 1].mx2);
    st[id].mxc = st[id << 1].mxc + st[id << 1 | 1].mxc;
  } else if (st[id << 1].mx1 > st[id << 1 | 1].mx1) {
    st[id].mx1 = st[id << 1].mx1;
    st[id].mx2 = max(st[id << 1].mx2, st[id << 1 | 1].mx1);
    st[id].mxc = st[id << 1].mxc;
  } else {
    st[id].mx1 = st[id << 1 | 1].mx1;
    st[id].mx2 = max(st[id << 1].mx1, st[id << 1 | 1].mx2);
    st[id].mxc = st[id << 1 | 1].mxc;
  }
  if (st[id << 1].mn1 == st[id << 1 | 1].mn1) {
    st[id].mn1 = st[id << 1].mn1;
    st[id].mn2 = min(st[id << 1].mn2, st[id << 1 | 1].mn2);
    st[id].mnc = st[id << 1].mnc + st[id << 1 | 1].mnc;
  } else if (st[id << 1].mn1 < st[id << 1 | 1].mn1) {
    st[id].mn1 = st[id << 1].mn1;
    st[id].mn2 = min(st[id << 1].mn2, st[id << 1 | 1].mn1);
    st[id].mnc = st[id << 1].mnc;
  } else {
    st[id].mn1 = st[id << 1 | 1].mn1;
    st[id].mn2 = min(st[id << 1].mn1, st[id << 1 | 1].mn2);
    st[id].mnc = st[id << 1 | 1].mnc;
  }
}
void build(int id, int l, int r) {
  if (l == r) {
    st[id] = Node(a[l]);
    st[id].lazy = 0;
    return;
  }
  int mid = l + r >> 1;
  build(id << 1, l, mid);
  build(id << 1 | 1, mid + 1, r);
  Merge(id);
  st[id].lazy = 0;
}
void push_max(int id, ll val, bool ok) {
  if (val >= st[id].mx1) return;
  st[id].sum -= st[id].mx1 * st[id].mxc;
  st[id].mx1 = val;
  st[id].sum += st[id].mx1 * st[id].mxc;
  if (ok) {
    st[id].mn1 = st[id].mx1;
  } else {
    if (val <= st[id].mn1) {
        st[id].mn1 = val;
    } else if (val < st[id].mn2) {
        st[id].mn2 = val;
    }
  }
}
void push_min(int id, ll val, bool ok) {
  if (val <= st[id].mn1) return;
  st[id].sum -= st[id].mn1 * st[id].mnc;
  st[id].mn1 = val;
  st[id].sum += st[id].mn1 * st[id].mnc;
  if (ok) st[id].mx1 = st[id].mn1;
  else {
    if (val >= st[id].mx1) {
      st[id].mx1 = val;
    } else if (val > st[id].mx2) st[id].mx2 = val;
  }
}
void push_add(int id, ll val, int l, int r) {
  if (val == 0) return;
  st[id].sum += 1ll * (r - l + 1) * val;
  st[id].mx1 += val;
  st[id].mn1 += val;
  if (st[id].mx2 != -INF) st[id].mx2 += val;
  if (st[id].mn2 != INF) st[id].mn2 += val;
  st[id].lazy += val;
}
void down(int id, int l, int r) {
  if (l == r) return;
  int mid = l + r >> 1;
  push_add(id << 1, st[id].lazy, l, mid);
  push_add(id << 1 | 1, st[id].lazy, mid + 1, r);
  st[id].lazy = 0;
  push_max(id << 1, st[id].mx1, l == mid);
  push_max(id << 1 | 1, st[id].mx1, mid + 1 == r);
  push_min(id << 1, st[id].mn1, l == mid);
  push_min(id << 1 | 1, st[id].mn1, mid + 1 == r);
}
void update_chmin(int id, int l, int r, int u, int v, ll val) {
  if (u > r || v < l || st[id].mx1 <= val) return;
  if (u <= l && r <= v && val > st[id].mx2) {
    push_max(id, val, l == r);
    return;
  }
  int mid = l + r >> 1;
  down(id, l, r);
  update_chmin(id << 1, l, mid, u, v, val);
  update_chmin(id << 1 | 1, mid + 1, r, u, v, val);
  Merge(id);
}
void update_chmax(int id, int l, int r, int u, int v, ll val) {
  if (u > r || v < l || st[id].mn1 >= val) return;
  if (u <= l && r <= v && st[id].mn2 > val) {
    push_min(id, val, l == r);
    return;
  }
  int mid = l + r >> 1;
  down(id, l, r);
  update_chmax(id << 1, l, mid, u, v, val);
  update_chmax(id << 1 | 1, mid + 1, r, u, v, val);
  Merge(id);
}
void update_add(int id, int l, int r, int u, int v, ll val) {
  if (u > r || v < l) return;
  if (u <= l && r <= v) {
    push_add(id, val, l, r);
    return;
  }
  int mid = l + r >> 1;
  down(id, l, r);
  update_add(id << 1, l, mid, u, v, val);
  update_add(id << 1 | 1, mid + 1, r, u, v, val);
  Merge(id);
}
ll get(int id, int l, int r, int u, int v) {
  if (u > r || v < l) return 0;
  if (u <= l && r <= v) return st[id].sum;
  int mid = l + r >> 1;
  down(id, l, r);
  return get(id << 1, l, mid, u, v) + get(id << 1 | 1, mid + 1, r, u, v);
}
