vector<int> sieve(int n) {
    vector<bool> prime(n + 1, true);

    for (int p = 2; p * p <= n; p++)
        if (prime[p])
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
    vector<int> primes;
    if (n >= 2)
        primes.emplace_back(2);
    for (int p = 3; p <= n; p += 2)
        if (prime[p])
            primes.emplace_back(p);
    return primes;
}