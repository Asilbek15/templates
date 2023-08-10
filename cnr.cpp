int cnr(int n, int r) {
    if (r > n)
        return 0;
    long long inv[r + 1];
    inv[0] = 1;
    if (r + 1 >= 2)
        inv[1] = 1;
    for (int i = 2; i <= r; i++) {
        inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    }
    int ans = 1;
    for (int i = 2; i <= r; i++) {
        ans = ((ans % mod) * (inv[i] % mod)) % mod;
    }
    for (int i = n; i >= (n - r + 1); i--) {
        ans = ((ans % mod) * (i % mod)) % mod;
    }
    return ans;
}