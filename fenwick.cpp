template<typename T> struct Fenwick {
    int n;
    vector<T> tree;

    void init(int len) {
        n = len;
        tree.assign(n + 1, 0);
    }

    void update(int i, T v) {
        for (i++; i <= n; i += i & (-i)) tree[i] += v;
    }

    T get(int i) {
        T sum = 0;
        for (i++; i > 0; i -= i & (-i)) sum += tree[i];
        return sum;
    }

    T get(int l, int r) {
        return get(r) - get(l - 1);
    }
};  