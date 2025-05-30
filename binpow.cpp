long long binpow(long long a, int b, long long mod) {
    a %= mod;
    long long res = 1;
    while (b) {
        if (b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}