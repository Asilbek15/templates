vector<int> prime_factors(int n) {
    vector<int> ans;
    while (n % 2 == 0) {
        ans.emplace_back(2);
        n /= 2;
    }
    while (n % 3 == 0) {
        ans.emplace_back(3);
        n /= 3;
    }
    for (int i = 5; i * i <= n; i += 2) {
        while (n % i == 0) {
            ans.emplace_back(i);
            n /= i;
        }
        while (n % (i + 2) == 0) {
            ans.emplace_back(i + 2);
            n /= i + 2;
        }
    }
    if (n > 1) ans.emplace_back(n);
    sort(ans.begin(), ans.end());
    return ans;
}