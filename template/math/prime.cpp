struct Prime {
    vector<int> minp, primes;

    Prime(int n)
    {
        sieve(n);
    }

    void sieve(int n)
    {
        minp.assign(n + 1, 0);
        primes.clear();

        for (int i = 2; i <= n; i++) {
            if (minp[i] == 0) {
                minp[i] = i;
                primes.push_back(i);
            }

            for (auto p : primes) {
                if (i * p > n) {
                    break;
                }
                minp[i * p] = p;
                if (p == minp[i]) {
                    break;
                }
            }
        }
    }
};

struct Prime {
    vector<int> minp, primes, phi;
    vector<int> b;

    Prime(int n)
    {
        sieve(n);
    }

    void sieve(int n)
    {
        minp.assign(n + 1, 0);
        b.assign(n + 1, 0);
        phi.assign(n + 1, 0);
        b[2] = 1;
        b[4] = 1;
        primes.clear();

        for (int i = 2; i <= n; i++) {
            if (minp[i] == 0) {
                minp[i] = i;
                primes.push_back(i);

                phi[i] = i - 1;
            }

            for (auto p : primes) {
                if (i * p > n) {
                    break;
                }
                minp[i * p] = p;
                if (p == minp[i]) {
                    phi[i * p] = phi[i] * p;
                    break;
                }
                phi[i * p] = phi[i] * (p - 1);
            }
        }
        for (int i = 1; i < sz(primes); i++) {
            for (i64 j = primes[i]; j <= n; j *= primes[i]) {
                b[j] = 1;
            }
            for (i64 j = primes[i] * 2; j <= n; j *= primes[i]) {
                b[j] = 1;
            }
        }
    }
} p(1e6);

namespace modules {
i64 eular_calc(i64 p, i64 exp)
{
    return power(p, exp - 1) * (p - 1);
}

int mu_calc(int p, int exp)
{
    if (exp > 1) {
        return 0;
    } else {
        return -1;
    }
}
}  // namespace modules

template <typename T>
struct OUniversal {
    std::vector<T>   f_1;     // f(n)
    std::vector<int> minp;    // 最小质因子
    std::vector<int> primes;  // 质数表
    std::vector<int> cnt;     // i 中 minp[i] 的幂次
    std::vector<int> part;    // i 去掉 minp[i]^cnt[i] 后的部分

    void init(int n, auto func_1)
    {
        f_1[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (minp[i] == 0) {
                minp[i] = i;
                primes.push_back(i);
                f_1[i]  = func_1(i, 1);
                cnt[i]  = 1;
                part[i] = 1;
            }
            for (int p : primes) {
                if (1LL * i * p > n) break;
                minp[i * p] = p;
                if (p == minp[i]) {
                    // i = part[i] * p^cnt[i]
                    cnt[i * p]  = cnt[i] + 1;
                    part[i * p] = part[i];
                    f_1[i * p]  = f_1[part[i]] * func_1(p, cnt[i * p]);
                    break;
                } else {
                    cnt[i * p]  = 1;
                    part[i * p] = i;
                    f_1[i * p]  = f_1[i] * func_1(p, 1);
                }
            }
        }
    }

    OUniversal(int n, auto func_1)
    {
        f_1.resize(n + 1);
        minp.resize(n + 1);
        cnt.resize(n + 1);
        part.resize(n + 1);
        init(n, func_1);
    }
};

struct ErSieve {
    int              n;
    std::vector<int> not_prime;
    std::vector<int> prime;

public:
    ErSieve(int _n)
    {
        n = _n;
        not_prime.resize(n + 1, 0);
        init();
    }

    void init()
    {
        not_prime[0] = not_prime[1] = 1;
        int sqrt_range              = int(sqrtl(n)) + 1;
        for (int i = 2; i <= sqrt_range; i++) {
            if (not_prime[i]) continue;
            for (int j = i * i; j <= n; j += i) {
                not_prime[j] = 1;
            }
        }
        for (int i = 2; i <= n; i++) {
            if (!not_prime[i]) prime.push_back(i);
        }
    }
};

template <typename T, typename Func>
struct Universal {
    std::vector<T>   f_1;
    std::vector<int> not_prime;
    std::vector<int> primes;
    std::vector<int> cnt;

    void init(int n, Func func_1)
    {
        f_1[1] = 1;
        for (i64 i = 2; i <= n; i++) {
            if (!not_prime[i]) {
                primes.push_back(i);
                f_1[i] = func_1(i, 1);
            }
            for (int p : primes) {
                not_prime[i * p] = 1;
                if (i % p == 0) {
                    cnt[i * p] = cnt[i] + 1;
                    f_1[i * p] = f_1[i] / func_1(p, cnt[i]) * func_1(p, cnt[i] + 1);
                    break;
                }
                cnt[i * p] = 1;
                f_1[i * p] = f_1[i] * func_1(p, 1);
            }
        }
    }

    Universal<T>(int n, Func func)
    {
        f_1.resize(n + 1);
        not_prime.resize(n + 1);
        cnt.resize(n + 1);
        init(n, func);
    }
};