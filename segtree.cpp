template<typename T> struct SegTree {
    vector<T> tree;
    int size;
    T neutral_element = -1e9; // sum - 0, mx - (-INF), mn - INF

    inline T merge(T a, T b) {
        return max(a, b);
    }

    void init(int n) {
        size = 1;
        while (size <= n) size *= 2;
        tree.assign(2 * size, neutral_element);
    }

    void build(vector<T> &a) {
        size = 1;
        while (size < a.size()) size *= 2;
        tree.assign(2 * size, neutral_element);
        for (int i = size; i < size + a.size(); i++) tree[i] = a[i - size];
        for (int i = size - 1; i > 0; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
    }

    void set(int p, T value) {  // set value at position p
        p += size;
        tree[p] = merge(value, tree[p]);
        for (; p > 1; p >>= 1) tree[p >> 1] = merge(tree[p], tree[p ^ 1]);
    }

    T get(int l, int r) {  // sum on interval [l, r]
        if (l > r) return neutral_element;
        T res = neutral_element;
        for (l += size, r += size + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = merge(res, tree[l++]);
            if (r & 1) res = merge(res, tree[--r]);
        }
        return res;
    }
};
