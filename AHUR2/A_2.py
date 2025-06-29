import math

MOD = 998244353
MOD2 = 998244352


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
            ans %= mod
        q >>= 1
        base *= base
        base %= mod
    return ans


prime = Prime(int(1e6))
t = int(input())
for _ in range(t):
    n, k = list(map(int, input().split()))
    k %= 402653184
    t -= 1
    ans = 1
    buffer = []
    sqrtN = math.isqrt(n)
    for p in prime.primes:
        if p <= sqrtN:
            q = 0
            a = 1
            while True:
                if p**a > n:
                    break
                q += qpow(n, k, MOD2) - qpow(n - n // p**a, k, MOD2)
                q %= MOD2
                a += 1
            ans *= qpow(p, q)
            ans %= MOD
        else:
            if len(buffer):
                if n // buffer[0] != n // p:
                    tempP = 1
                    for i in buffer:
                        tempP *= i
                        tempP %= MOD
                    ans *= qpow(
                        tempP,
                        (qpow(n, k, MOD2) - qpow(n - n // buffer[0], k, MOD2)) % MOD2,
                    )
                    ans %= MOD
                    buffer = []
                buffer.append(p)
            else:
                buffer.append(p)
    if len(buffer) != 0:
        tempP = 1
        for i in buffer:
            tempP *= i
            tempP %= MOD
        ans *= qpow(tempP, qpow(n, k, MOD2) - qpow(n - n // buffer[0], k, MOD2))
        ans %= MOD
        buffer = []
    print(ans)
