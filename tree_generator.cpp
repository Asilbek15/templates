vector<vector<int>> generate_tree(int n) {
    struct dsu {
        vector<int> p, size;

        void init(int n) {
            p.assign(n + 1, 0);
            size.assign(n + 1, 1);
            for (int i = 1; i <= n; i++)
                p[i] = i;
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
    vector<vector<int>> g(n + 1);
    dsu ds; ds.init(n + 1);
    int cnt = n;
    while (cnt != 1) {
        int u = rand(1ll, n), v = rand(1ll, n);
        if (ds.get(u) == ds.get(v)) continue;
        cnt--;
        ds.add(u, v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    return g;
}