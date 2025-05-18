struct SegmentTree {
    int n;
    std::vector<int> sum;
    SegmentTree(int n) : n(n), sum(4 * n) {}
    void pull(int p) {
        sum[p] = sum[2 * p] + sum[2 * p + 1];
    }
    void modify(int p, int l, int r, int x, int val) {
        if (r - l == 1) {
            sum[p] += val;
        } else {
            int m = (l + r) / 2;
            if (x < m) {
                modify(2 * p, l, m, x, val);
            } else {
                modify(2 * p + 1, m, r, x, val);
            }
            pull(p);
        }
    }
    void modify(int x, int val) {
        modify(1, 0, n, x, val);
    }
    int select(int p, int l, int r, int k) {
        if (r - l == 1) {
            return l;
        } else {
            int m = (l + r) / 2;
            if (k < sum[2 * p]) {
                return select(2 * p, l, m, k);
            } else {
                return select(2 * p + 1, m, r, k - sum[2 * p]);
            }
        }
    }
    int select(int k) {
        return select(1, 0, n, k);
    }
};