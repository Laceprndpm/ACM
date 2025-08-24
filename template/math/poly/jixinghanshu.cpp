#include <bits/stdc++.h>

#include <functional>
#include <vector>

template <typename T, typename Func>
struct OUniversal {
    std::vector<T>   f;       // f(n)
    std::vector<int> minp;    // 最小质因子
    std::vector<int> primes;  // 质数表
    std::vector<int> cnt;     // i 中 lp[i] 的幂次
    std::vector<int> part;    // i 去掉 lp[i]^cnt[i] 后的部分

    void init(int n, Func func)
    {
        f[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (minp[i] == 0) {
                minp[i] = i;
                primes.push_back(i);
                f[i]    = func(i, 1);
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
                    f[i * p]    = f[part[i]] * func(p, cnt[i * p]);
                    break;
                } else {
                    cnt[i * p]  = 1;
                    part[i * p] = i;
                    f[i * p]    = f[i] * func(p, 1);
                }
            }
        }
    }

    OUniversal(int n, Func func)
    {
        f.resize(n + 1);
        minp.resize(n + 1);
        cnt.resize(n + 1);
        part.resize(n + 1);
        init(n, func);
    }
};

int main() {}