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