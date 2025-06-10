import math

MOD = 998244353

T = int(input())


def qpow(base: int, q: int):
    ans = 1
    while q:
        if q & 1:
            ans *= base
            ans %= MOD
        q >>= 1
        base *= base
        base %= MOD
    return ans


for _ in range(T):
    n, k = list(map(int, input().split()))
    arr = [0] * int(1e3 + 1)
    for i in range(1001):
        arr[i] = qpow(i, k)
    dp = [0] * int(1e6 + 1)
    for i in range(int(1e6), int(1e3), -1):
        dp[i] += arr[int(1e6) // i]  # = 1e6 / i ** k
        # for j in range(1, int(math.sqrt(i)) + 1, 1):
        #     if i % j == 0:
        #         if j != 1:
        #             dp[i // j] -= dp[i]
        #         if j * j != i:
        #             dp[i // (i // j)] -= dp[i]
        for j in range(1, int(1e6 + 1)):
            if j * i > int(1e6):
                break
            dp[i] -= dp[i * j]

    for i in range(int(1e3), 0, -1):
        dp[i] += qpow(int(1e6) // i, k)
        # for j in range(1, int(math.sqrt(i)) + 1, 1):
        #     if i % j == 0:
        #         if j != 1:
        #             dp[i // j] -= dp[i]
        #         if j * j != i:
        #             dp[i // (i // j)] -= dp[i]
        for j in range(1, int(1e6 + 1)):
            if j * i > int(1e6):
                break
            dp[i] -= dp[i * j]

    ans = 1
    for i in range(int(n + 1)):
        ans *= qpow(i, dp[i])
        ans %= MOD
    print(ans)

    # 对于i > 1e3，可以预处理
    # i <= 1e3，则只计算
