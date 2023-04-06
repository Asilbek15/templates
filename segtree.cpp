template<typename T> struct SegTree {
    vector<T> tree;
    int size, len;
    T neutral_element; // sum - 0, mx - (-INF), mn - INF
 
    void init(int n) {
        len = n;
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size - 1, neutral_element);
    }
 
    T type(T f, T s) {
        // return something
    }
 
    void build(vector<T> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < a.size())
                tree[x] = a[lx];
        } else {
            int m = lx + rx >> 1;
            build(a, 2 * x + 1, lx, m);
            build(a, 2 * x + 2, m, rx);
            tree[x] = type(tree[2 * x + 1], tree[2 * x + 2]);
        }
    }
 
    void build(vector<T> &a) {
        init(a.size());
        build(a, 0, 0, size);
    }
 
    void set(int i, T v, int x, int lx, int rx, bool add) {
        if (rx - lx == 1) {
            if (add) {
                tree[x] = type(tree[x], v);
            }
            else {
                tree[x] = v;
            }
            return;
        }
        int m = (lx + rx) >> 1;
        if (i < m) {
            set(i, v, 2 * x + 1, lx, m, add);
        } else {
            set(i, v, 2 * x + 2, m, rx, add);
        }
        tree[x] = type(tree[2 * x + 1], tree[2 * x + 2]);
    }
 
    void set(int i, T v, bool add = false) {
        if (i >= len) return;
        set(i, v, 0, 0, size, add);
    }
 
    T get(int l, int r, int x, int lx, int rx) {
        if (l >= rx or lx >= r) return neutral_element;
        if (l <= lx and rx <= r) return tree[x];
        int m = lx + rx >> 1;
        T s1 = get(l, r, 2 * x + 1, lx, m);
        T s2 = get(l, r, 2 * x + 2, m, rx);
        return type(s1, s2);
    }
 
    T get(int l, int r) {
        r++;
        return get(l, r, 0, 0, size);
    }
};