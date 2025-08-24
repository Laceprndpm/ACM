#include <vector>
using namespace std;
using i64 = long long;

// phi = n \cdot \prod_{p | n} (1 - (1 / p))
i64 get_phi(i64 n)
{
    i64 phi = 1;
    for (int i = 2; i <= n / i; i++) {
        // 质数
        if (n % i == 0) {
            // 第一个乘上prod部分的 i - 1
            phi *= (i - 1);
            n /= i;
            // 后续只能乘n内的i
            while (n % i == 0) phi *= i, n /= i;
        }
    }
    // 尾判
    if (n > 1) phi *= (n - 1);
    return phi;
}

struct Phi {
    vector<int> phi;
    vector<int> primes;

    void init(int n)
    {
        int total = 0;
        phi[1]    = 1;
        for (int i = 2; i <= n; i++) {
            if (!phi[i]) {
                primes[total++] = i;
                phi[i]          = i - 1;
            }
            for (int j = 0; j < total && i * primes[j] <= n; j++) {
                if (i % primes[j] == 0) {
                    phi[i * primes[j]] = phi[i] * primes[j];
                    break;
                } else {
                    phi[i * primes[j]] = phi[i] * (primes[j] - 1);
                }
            }
        }
    }
};

// floor(p / i) * i + p % i == p
// floor(p / i) * i + p % i == 0 (mod p)
// inv[i] == -inv[p % i] * floor(p / i)
//
//

struct Prime {
    vector<int> minp;
    vector<int> primes;

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