# WA
# deprecated

import math

MOD = 998244353
MOD2 = 998244352
T = int(input())


class Prime:
    def __init__(self, n):
        self.minp = [0] * (n + 1)
        self.primes = []
        self.sieve(n)

    def sieve(self, n):
        for i in range(2, n + 1):
            if self.minp[i] == 0:
                self.minp[i] = i
                self.primes.append(i)
            for p in self.primes:
                if i * p > n:
                    break
                self.minp[i * p] = p
                if p == self.minp[i]:
                    break


def qpow(base: int, q: int, mod: int = MOD):
    ans = 1
    while q:
        if q & 1:
            ans *= base
            ans %= MOD
        q >>= 1
        base *= base
        base %= MOD
    return ans


prime = Prime(10**6)
for _ in range(T):
    n, k = list(map(int, input().split()))
    arr = [0] * int(1e3 + 1)
    for i in range(1001):
        arr[i] = qpow(i, k, MOD2)
    dp = [0] * int(1e6 + 1)
    for i in range(int(n), int(math.sqrt(int(n))), -1):
        dp[i] += arr[int(n) // i]  # = 1e6 / i ** k
        dp[i] %= 998244352
        for j in range(2, int(1e6 + 1)):
            if j * i > int(n):
                break
            dp[i] -= dp[i * j]
            dp[i] %= 998244352

    for i in range(int(math.sqrt(int(n))), 0, -1):
        dp[i] += qpow(n // i, k, MOD2)
        # for j in range(1, int(math.sqrt(i)) + 1, 1):
        #     if i % j == 0:
        #         if j != 1:
        #             dp[i // j] -= dp[i]
        #         if j * j != i:
        #             dp[i // (i // j)] -= dp[i]
        for j in range(2, int(1e6 + 1)):
            if j * i > int(n):
                break
            dp[i] -= dp[i * j]
            dp[i] %= 998244352

    under = 1
    base = 1
    for i in range(1, int(n + 1)):
        base *= i
    base = qpow(base, k * qpow(n, k - 1, MOD2))
    for i in range(1, int(n + 1)):
        under *= qpow(i, dp[i])
        under %= MOD
    ans = base * qpow(under, MOD - 2) % MOD
    print(ans)

    # 对于i > 1e3，可以预处理
    # i <= 1e3，则只计算
