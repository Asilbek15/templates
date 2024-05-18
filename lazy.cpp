template<typename T> struct LazySegTree {
    struct Node {
        T val, lazy;

        Node() {
            // maybe changes
            val = 1e18; // sum - 0, max - (-LLINF), min - LLINF
            lazy = 0;
        }

        Node operator=(const T x) {
            val = x;
            lazy = 0;
            return *this;
        }

        void merge(const Node &a, const Node &b) {
            val = std::min(a.val, b.val);
        }

        void impact(T v) {
            // maybe changes
            val += v;
            lazy += v;
        }

        void propagate(Node &a, Node &b) {
            // maybe changes
            if (lazy != 0) {
                a.impact(lazy);
                b.impact(lazy);
                lazy = 0;
            }
        }
    };

    vector<Node> tree;
    Node neutral_element;
    int size;

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        Node zeros;
        zeros.val = 0;
        tree.assign(2 * size - 1, zeros);
    }

     void build(vector<T> &a) {
        size = 1;
        while (size < a.size()) size *= 2;
        tree.assign(2 * size, neutral_element);
        for (int i = size - 1; i < size - 1 + a.size(); i++) tree[i] = a[i - size + 1];
        for (int i = size - 2; i >= 0; i--) tree[i].merge(tree[i * 2 + 1], tree[i * 2 + 2]);
     }


    void upd(int l, int r, T v, int x, int lx, int rx) {
        if (l >= rx or lx >= r) return;
        if (l <= lx and rx <= r) {
            tree[x].impact(v);
            return;
        }
        tree[x].propagate(tree[2 * x + 1], tree[2 * x + 2]);
        int mid = (lx + rx) >> 1;
        upd(l, r, v, 2 * x + 1, lx, mid);
        upd(l, r, v, 2 * x + 2, mid, rx);
        tree[x].merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void upd(int l, int r, T v) { // [l, r]
        upd(l, r + 1, v, 0, 0, size);
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