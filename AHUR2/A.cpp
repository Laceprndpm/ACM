/**
 *@author ChatGPT（基于 GPT-4o-mini）
 */
// This code was translated and adapted by ChatGPT, an AI language model based on GPT-4o-mini.
// The assistant's role was to convert Python logic into equivalent C++ code,
// focusing on preserving functionality while maintaining clarity and performance.
// Python’s ease is great for prototyping, but damn, it can seriously drag you down when it counts.

#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;

const i64 MOD  = 998244353;
const i64 MOD2 = 998244352;

struct Prime {
    vector<int> minp, primes;

    Prime(int n)
    {
        minp.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            if (minp[i] == 0) {
                minp[i] = i;
                primes.push_back(i);
            }
            for (int p : primes) {
                if ((i * 1LL * p) > n) break;
                minp[i * p] = p;
                if (p == minp[i]) break;
            }
        }
    }
};

i64 qpow(i64 base, i64 exp, i64 mod)
{
    i64 res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Prime prime(int(1e6));

    int T;
    cin >> T;
    while (T--) {
        string K;
        i64    n, k;
        cin >> n >> K;
        k       = 0;
        int len = K.length();
        for (int i = 0; i < len; i++)
            k = ((10ll * k + K[i] - '0') + 402653184) % 402653184;

        i64         ans = 1;
        vector<int> buffer;
        int         sqrtN = (int)sqrtl(n);

        for (auto p : prime.primes) {
            if (p <= sqrtN) {
                i64 q = 0;
                i64 a = 1;
                while (true) {
                    i64 powpa = 1;
                    for (i64 _ = 0; _ < a; _++)
                        powpa *= p;  // p^a
                    if (powpa > n) break;

                    q += qpow(n, k, MOD2) - qpow(n - n / powpa, k, MOD2);
                    q %= MOD2;
                    a++;
                }
                ans = (ans * qpow(p, (q + MOD2) % MOD2, MOD)) % MOD;
            } else {
                if (!buffer.empty() && n / buffer[0] != n / p) {
                    i64 tempP = 1;
                    for (auto i : buffer) {
                        tempP = (tempP * i) % MOD;
                    }
                    i64 e = (qpow(n, k, MOD2) - qpow(n - n / buffer[0], k, MOD2) + MOD2) % MOD2;
                    ans   = (ans * qpow(tempP, e, MOD)) % MOD;
                    buffer.clear();
                }
                buffer.push_back(p);
            }

            // 这一部分是 Python
            // 代码最后多余的块逻辑，Python里清空buffer。C++不需要这么写，缓冲区逻辑只在for循环后处理即可
        }

        if (!buffer.empty()) {
            i64 tempP = 1;
            for (auto i : buffer) {
                tempP = (tempP * i) % MOD;
            }
            i64 e = (qpow(n, k, MOD2) - qpow(n - n / buffer.back(), k, MOD2) + MOD2) % MOD2;
            ans   = (ans * qpow(tempP, e, MOD)) % MOD;
            buffer.clear();
        }

        cout << ans << "\n";
    }
    return 0;
}
