template<typename T> struct Fenwick {
    int n;
    vector<T> tree;

    void init(int len) {
        n = len;
        tree.assign(n + 1, 0);
    }

    void build(vector<T> a) {
        n = a.size();
        tree.assign(n + 1, 0);
        for (int i = 0; i < n; i++) {
            update(i, a[i]);
        }
    }

    void update(int i, T v) {
        i++;
        while (i <= n) {
            tree[i] += v;
            i += i & (-i);
        }
    }

    T get(int i) {
        T sum = 0;
        i++;
        while (i > 0) {
            sum += tree[i];
            i -= i & (-i);
        }
        return sum;
    }

    T get(int l, int r) {
        return get(r) - get(l - 1);
    }
};  