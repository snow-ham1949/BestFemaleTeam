struct SegTree {
    size_t n;
    vector<int64_t> data;
    vector<int> xs;
    void reserve(int i) { xs.push_back(i); }
    void build0() {
        sort(xs.begin(), xs.end());
        for (n = 1; n < xs.size(); n <<= 1);
        data.resize(n << 1);
    }
    void build1() {
        for (int i = n; --i; ) data[i] = data[i << 1] + data[i << 1 | 1];
    }
    void add_pre(int i, int val) {
        i = lower_bound(xs.begin(), xs.end(), i) - xs.begin();
        data[i + n] += val;
    }
    void add(int i, int val) {
        i = lower_bound(xs.begin(), xs.end(), i) - xs.begin();
        for (i += n; i; i >>= 1) data[i] += val;
    }
    int64_t sum(int l, int r) {
        l = lower_bound(xs.begin(), xs.end(), l) - xs.begin();
        r = lower_bound(xs.begin(), xs.end(), r) - xs.begin();
        int64_t res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (r & 1) res += data[--r];
            if (l & 1) res += data[l++];
        }
        return res;
    }
};
struct SegTree2D {
    size_t n;
    vector<SegTree> trees;
    SegTree2D (size_t n_) {
        for (n = 1; n < n_; n <<= 1);
        trees.resize(n << 1);
    }
    void reserve(int i, int j) { // 1. for all node(x, y), call reserve(x, y)
        for (i += n; i; i >>= 1) trees[i].reserve(j);
    }
    void build0() { // 2. 
        for (auto &i : trees) i.build0();
    }
    void build1() { // 4.
        for (auto &i : trees) i.build1();
    }
    void add_pre(int i, int j, int val) { // 3. 
        for (i += n; i; i >>= 1) trees[i].add_pre(j, val);
    }
    // operations: add / sum
    void add(int i, int j, int val) {
        for (i += n; i; i >>= 1) trees[i].add(j, val);
    }
    int64_t sum(int l0, int r0, int l1, int r1) {// x in [l0, r0), y in [l1, r1)
        int64_t res = 0;
        for (l0 += n, r0 += n; l0 < r0; l0 >>= 1, r0 >>= 1) {
            if (r0 & 1) res += trees[--r0].sum(l1, r1);
            if (l0 & 1) res += trees[l0++].sum(l1, r1);
        }
        return res;
    }
};
