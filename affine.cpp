template<typename T> struct AffineSegTree {
    struct Node {
        T val, k, b, cnt;

        Node() {
            val = b = cnt = 0;
            k = 1;
        }

        Node operator=(const T x) {
            val = x;
            k = cnt = 1, b = 0;
            return *this;
        }

        void merge(const Node &a, const Node &b) {
            val = (a.val + b.val) % mod;
            cnt = a.cnt + b.cnt;
        }

        void impact(T uk, T ub) {
            // maybe changes
            val = (val * uk + ub * cnt) % mod;
            k = (k * uk) % mod;
            b = (uk * b + ub) % mod;
        }

        void propagate(Node &left, Node &right) {
            // maybe changes
            if (k != 1 or b != 0) {
                left.impact(k, b);
                right.impact(k, b);
                k = 1, b = 0;
            }
        }
    };

    vector<Node> tree;
    Node neutral_element;
    int size;

    void build(vector<T> &a) {
        size = 1;
        while (size < a.size()) size *= 2;
        tree.assign(2 * size, neutral_element);
        for (int i = size - 1; i < size - 1 + a.size(); i++) tree[i] = a[i - size + 1];
        for (int i = size - 2; i >= 0; i--) tree[i].merge(tree[i * 2 + 1], tree[i * 2 + 2]);
    }

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        Node zeros;
        zeros.val = 0;
        tree.assign(2 * size - 1, zeros);
    }

    void set(int l, int r, T k, T b, int x, int lx, int rx) {
        if (l >= rx or lx >= r) return;
        if (l <= lx and rx <= r) {
            tree[x].impact(k, b);
            return;
        }
        tree[x].propagate(tree[2 * x + 1], tree[2 * x + 2]);
        int mid = (lx + rx) >> 1;
        set(l, r, k, b, 2 * x + 1, lx, mid);
        set(l, r, k, b, 2 * x + 2, mid, rx);
        tree[x].merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set(int l, int r, T k, T b) { // [l, r]
        set(l, r + 1, k, b, 0, 0, size);
    }

    Node get(int l, int r, int x, int lx, int rx) {
        if (l >= rx or lx >= r) return neutral_element;
        if (l <= lx and rx <= r) return tree[x];
        tree[x].propagate(tree[2 * x + 1], tree[2 * x + 2]);
        int mid = (lx + rx) >> 1;
        Node ans;
        ans.merge(get(l, r, 2 * x + 1, lx, mid), get(l, r, 2 * x + 2, mid, rx));
        return ans;
    }

    T get(int l, int r) { // [l, r]
        return get(l, r + 1, 0, 0, size).val;
    }
};
