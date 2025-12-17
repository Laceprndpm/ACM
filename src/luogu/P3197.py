import math

m, n = map(int, input().split())
MOD = 100003
ans = pow(m - 1, n - 1, MOD) * m
ans %= MOD
ans = pow(m, n, MOD) - ans
print(ans % MOD)
