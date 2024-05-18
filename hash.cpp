vector<int> primes_list = {993146723,996752089,993912011,993276811,990439561,999134321,1000034863,990310561,1002852971,990902071,1002552547,1004791829,1006000901,1000242487,998810363,998510393,1005429353,1006591627,1007173513,1001089151,1007873257,1002742243,997222561,995034571,993148837,1007335169,1007688763,1000458911,995690771,1000963499,1004540941,996669341,1009791163,1005362731,990259279,1004949923,999257549,994083157,997000859,991488709,990129697,991686341,1006200047,995269721,998938153,1001274091,1008215713,1005259139,990913177,1000705361,992677943,1001761259,1008933127,991650763,1003413907,1001591489,999972499,1001013547,996769511,1001061553,998571107,1005498281,1004864467,1008537151,995490059,994271963,1000330937,1007601659,999935701,1007473871,1005960979,1009408901,1003306259,1001731277,993759673,1005202493,994289501,992293103,1007638627,991446553,991299677,1007753729,1003063247,1008357107,995452751,995169853,993065287,1009534639,991566083,995628827,992550289,993078701,1009667231,996338407,996761473,1008855797,1005879461,1000745609,997377253,1000759181};
const int K = 1; // change this
int base[K], mod[K];
vector<array<int, K>> modPow(1);

void assignHashes() {
    mt19937 rngHash(chrono::high_resolution_clock::now().time_since_epoch().count());
    for (int i = 0; i < K; i++) {
        int j = rngHash() % (int) primes_list.size();
        mod[i] = primes_list[j];
        base[i] = rngHash() % (mod[i] - 2) + 2;
        modPow[0][i] = 1;
    }
}

struct __hash {
    vector<array<int, K>> h;
 
    inline void init(const vector<int> &a) {
        if (base[0] == 0) assignHashes();

        int n = (int) a.size(), sz = modPow.size();
        h.resize(n);

        if (sz <= n) {
            modPow.resize(n + 1);
            for (int i = sz; i <= n; i++){
                for (int j = 0; j < K; j++) {
                    modPow[i][j] = 1ll * modPow[i - 1][j] * base[j] % mod[j];
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < K; j++) {
                h[i][j] = a[i] % mod[j];
                if (i > 0) h[i][j] = (1ll * h[i - 1][j] * base[j] + h[i][j]) % mod[j];
            }
        }
    }
 
    inline void init(const string &s) {
        int n = (int) s.size();
        vector<int> a(n);
        for (int i = 0; i < n; i++) a[i] = (int) s[i];
        init(a);
    }
 
    inline int get(int j, int l, int r) {
        assert(l <= r);
        int res = h[r][j];
        if (l > 0){
            res -= (long long) modPow[r - l + 1][j] * h[l - 1][j] % mod[j];
            if (res < 0) res += mod[j];
        }
        return res;
    }
 
    inline array<int, K> get(int l, int r) {
        array<int, K> res{};
        for (int j = 0; j < K; j++) res[j] = get(j, l, r);
        return res;
    }
 
    inline bool same(int l1, int r1, int l2, int r2) {
        return get(l1, r1) == get(l2, r2);
    }
};