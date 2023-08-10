struct SegTree_st {
    struct node {
        // change this
        node operator=(int x) {
            // change
            return *this;
        }
    };
    vector<node> tree;
    int size;
    node neutral_element; // change this

    void init(int n) {
        size = 1;
        while (size <= n) size *= 2;
        tree.assign(2 * size, neutral_element);
    }

    node type(node a, node b) {
        // change this
    }

    SegTree_st(int n) {
        init(n);
    }

    SegTree_st() {}

    void set(int value, int p) {  // set value at position p
        p += size;
        node nd;
        nd = value;
        tree[p] = type(nd, tree[p]);
        for (; p > 1; p >>= 1) tree[p >> 1] = type(tree[p], tree[p ^ 1]);
    }

    node get(int l, int r) {  // sum on interval [l, r]
        if (l > r) return neutral_element;
        node res = neutral_element;
        for (l += size, r += size + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = type(res, tree[l++]);
            if (r & 1) res = type(res, tree[--r]);
        }
        return res;
    }
};