struct lca {
    struct node {
        int depth, parent, jump;
    };

    vector<node> info;

    lca(const vector<vector<int>> &adj, int root) {
        info.resize(adj.size());
        dfs(root, root, adj);
    }

    void dfs(int node, int par, const vector<vector<int>> &adj) {
        int par2 = info[par].jump;
        info[node] = {
            info[par].depth + 1,
            par,
            info[par].depth - info[par2].depth == info[par2].depth - info[info[par2].jump].depth ? info[par2].jump : par
        };
        for (int to: adj[node]) {
            if (to == par) continue;
            dfs(to, node, adj);
        }
    }

    int kthPar(int node, int k) {
		while (k > 0 && node > 0) {
			if (info[node].depth - k <= info[info[node].jump].depth) {
				k -= info[node].depth - info[info[node].jump].depth;
				node = info[node].jump;
			} else {
				k--;
				node = info[node].parent;
			}
		}
		return node;
	}
 
	int getLca(int x, int y) {
		if (info[x].depth < info[y].depth) swap(x, y);
		x = kthPar(x, info[x].depth - info[y].depth);
		if (x == y) return x;
		while (x != y) {
			if (info[x].jump == info[y].jump) {
				x = info[x].parent;
				y = info[y].parent;
			} else {
				x = info[x].jump;
				y = info[y].jump;
			}
		}
		return x;
	}
 
	int distEdges(int x, int y) {
		return info[x].depth + info[y].depth - 2 * info[getLca(x, y)].depth;
	}
};