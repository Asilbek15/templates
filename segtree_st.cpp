struct SegTree_st {
    struct node {

    };
    vector<node> tree;
    int size;
    node neutral_element; // sum - 0, mx - (-INF), mn - INF

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        tree.assign(2 * size - 1, neutral_element);
    }


    node type(node f, node s) {
        // return something
    }

    void set(int i, node v, int x, int lx, int rx, bool add) {
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

    void set(int i, node v, bool add = false) {
        set(i, v, 0, 0, size, add);
    }

    node get(int l, int r, int x, int lx, int rx) {
        if (l >= rx or lx >= r) return neutral_element;
        if (l <= lx and rx <= r) return tree[x];
        int m = lx + rx >> 1;
        node s1 = get(l, r, 2 * x + 1, lx, m);
        node s2 = get(l, r, 2 * x + 2, m, rx);
        return type(s1, s2);
    }

    node get(int l, int r) {
        return get(l, r + 1, 0, 0, size);
    }
};