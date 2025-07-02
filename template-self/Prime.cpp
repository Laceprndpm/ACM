class Prime_Old {
    i64               n;
    std::vector<bool> _is_prime;
    std::vector<int>  prime;

public:
    [[deprecated("old")]]
    Prime_Old(i64 _n)
        : n(_n), _is_prime(n + 1, true)
    {
        sieve();
    }

    void sieve()
    {
        for (int i = 2; i <= n; i++) {
            if (_is_prime[i]) {
                prime.push_back(i);
            }
            for (int j : prime) {
                if (j * i > n) break;
                _is_prime[j * i] = false;
                if (i % j == 0) break;
            }
        }
    }

    [[deprecated("O(n log log n)")]]
    void sieve_old()
    {
        _is_prime[0] = _is_prime[1] = false;
        int i;
        for (i = 2; i * i <= n; ++i) {
            if (_is_prime[i]) {
                prime.push_back(i);
                for (int j = i * i; j <= n; j += i) {
                    _is_prime[j] = false;
                }
            }
        }
        for (; i <= n; i++) {
            if (_is_prime[i]) {
                prime.push_back(i);
            }
        }
    }

    bool is_prime(int x) const noexcept
    {
        assert(x >= 2 && x <= n);
        return _is_prime[x];
    }

    const vector<int>& get_prime() const noexcept
    {
        return prime;
    }
};

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

struct Phi {
    vector<int> phi;
    vector<int> p;

    void init(int n)
    {
        int total = 0;
        phi[1]    = 1;
        for (int i = 2; i <= n; i++) {
            if (!phi[i]) {
                p[total++] = i;
                phi[i]     = i - 1;
            }
            for (int j = 0; j < total && i * p[j] <= n; j++) {
                if (i % p[j] == 0) {
                    phi[i * p[j]] = phi[i] * p[j];
                    break;
                } else {
                    phi[i * p[j]] = phi[i] * (p[j] - 1);
                }
            }
        }
    }
};
