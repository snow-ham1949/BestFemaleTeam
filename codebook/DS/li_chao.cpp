using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

constexpr ll INF = 3 * TEN(18);
struct LiChaoTree {
    using L = pair<ll, ll>;  // l.first * x + l.second
    int sz;
    V<L> data;
    V<ll> xs;
    static ll eval(L l, ll x) { return l.first * x + l.second; }
    LiChaoTree(V<ll> _xs) : xs(_xs) { // xs stores all x appears in this problem
        int n = int(xs.size());
        int lg = 1;
        while ((1 << lg) < n) lg++;
        sz = 1 << lg;
        while (int(xs.size()) < sz) xs.push_back(TEN(9));
        data = V<L>(2 * sz, L(0, 3 * TEN(18)));
    }
    void add(L line, int l, int r) { // add({a, b}, l, r): add a segment f(x) = a*x+b, x in [l, r]
        l = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
        r = lower_bound(xs.begin(), xs.end(), r) - xs.begin();
        add(line, l, r, 0, sz, 1);
    }
    ll query(ll x) { // query(a) : find the minimal y when x=a
        int k = int(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
        k += sz;
        ll ans = INF;
        while (k >= 1) {
            ans = min(ans, eval(data[k], x));
            k >>= 1;
        }
        return ans;
    }

  private:
    void add(L line, int ql, int qr, int l, int r, int k) {
        if (qr <= l || r <= ql) {
            return;
        } else if (ql <= l && r <= qr) {
            int mid = (l + r) / 2;
            ll mx = xs[mid];
            if (eval(line, mx) < eval(data[k], mx)) {
                swap(line, data[k]);
            }
            if (l + 1 == r) return;
            if (line.first > data[k].first) {
                add(line, ql, qr, l, mid, 2 * k);
            } else if (line.first < data[k].first) {
                add(line, ql, qr, mid, r, 2 * k + 1);
            }
        } else {
            int mid = (l + r) / 2;
            add(line, ql, qr, l, mid, 2 * k);
            add(line, ql, qr, mid, r, 2 * k + 1);
        }
    }
};
