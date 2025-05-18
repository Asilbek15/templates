struct dsu {
    vector<int> p, size;

    void init(int n) {
        p.assign(n + 1, 0);
        size.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) p[i] = i;
    }

    int get(int a) {
        return (p[a] == a ? a : p[a] = get(p[a]));
    }

    void add(int a, int b) {
        a = get(a);
        b = get(b);
        if (a == b) return;
        if (size[a] > size[b]) swap(a, b);
        size[b] += size[a];
        p[a] = b;
    }
};