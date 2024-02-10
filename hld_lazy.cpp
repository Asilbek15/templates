struct hld {
    template<typename T> struct SegTree {
        vector<T> tree;
        int size;
        T neutral_element = -1e9; // sum - 0, mx - (-INF), mn - INF

        inline T merge(T a, T b) {
            return max(a, b);
        }

        void build(vector<T> &a) {
            size = 1;
            while (size < a.size()) size *= 2;
            tree.assign(2 * size, neutral_element);
            for (int i = size; i < size + a.size(); i++) tree[i] = a[i - size];
            for (int i = size - 1; i > 0; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }

        void set(int p, int value) {  // set value at position p
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

    vector<int> parent, depth, heavy, head, pos;
    SegTree<int> sg;
    int z;


    int dfs(int u, vector<vector<int>> &adj) {
        int size = 1, max_child_size = 0;
        for (int v: adj[u]) {
            if (parent[u] == v) continue;
            parent[v] = u; depth[v] = depth[u] + 1;
            int child_size = dfs(v, adj);
            size += child_size;
            if (max_child_size < child_size) {
                heavy[u] = v;
                max_child_size = child_size;
            }
        }
        return size;
    }

    void decompose(int u, int h, vector<vector<int>> &adj) {
        head[u] = h; pos[u] = z++;
        if (heavy[u] != -1) decompose(heavy[u], h, adj);
        for (int v: adj[u]) {
            if (v != parent[u] and v != heavy[u]) {
                decompose(v, v, adj);
            }
        }
    }

    void init(vector<vector<int>> &adj, vector<int> &a, int root = 0) {
        int n = (int) adj.size();
        parent.assign(n, 0); depth.assign(n + 1, 0);
        heavy.assign(n + 1, -1); head.assign(n + 1, 0);
        pos.assign(n + 1, -1); z = 0;
        dfs(root, adj);
        decompose(root, root, adj);
        vector<int> vec(n);
        for (int i = 0; i < n; i++) {
            if (pos[i] != -1) vec[pos[i]] = a[i];
        }
        sg.build(vec);
    }

    int query(int a, int b) {
        int res = 0;
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] > depth[head[b]]) swap(a, b);
            res = max(res, sg.get(pos[head[b]], pos[b]));
        }
        if (depth[a] > depth[b]) swap(a, b);
        res = max(res, sg.get(pos[a], pos[b]));
        return res;
    }

    void upd(int a, int val) { sg.set(pos[a], val); }
};