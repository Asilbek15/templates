template<typename T> struct SegTree {
    vector<T> tree;
    int size;
    T neutral_element = -1e9; // sum - 0, mx - (-INF), mn - INF

    void init(int n) {
        size = 1;
        while (size <= n) size *= 2;
        tree.assign(2 * size, neutral_element);
    }

    inline T type(T a, T b) {
        return max(a, b);
    }

    SegTree(int n) {
        init(n);
    }

    SegTree() {}

    void set(int value, int p) {  // set value at position p
        p += size;
        tree[p] = type(value, tree[p]);
        for (; p > 1; p >>= 1) tree[p >> 1] = type(tree[p], tree[p ^ 1]);
    }

    T get(int l, int r) {  // sum on interval [l, r]
        if (l > r) return neutral_element;
        int res = neutral_element;
        for (l += size, r += size + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = type(res, tree[l++]);
            if (r & 1) res = type(res, tree[--r]);
        }
        return res;
    }
};