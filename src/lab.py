import math
import sys
input = sys.stdin.read

def init():
    return int(input())

def print(x):
    if x < 0:
        x = -x
        sys.stdout.write('-')
    if x // 10:
        print(x // 10)
    sys.stdout.write(str(x % 10))

N = 100 + 5
n, X = init()
p = [0] * N
dp = [[float('inf')] * N for _ in range(N)]
num = [0] * N

s = []
for _ in range(n):
    s.append((init(), init()))

def mn(x, y):
    return x if x < y else y

Ans = float('inf')

def cmp(x, y, z):
    return math.log2(x) + z * math.log2(y) >= math.log2(X)

def quick_mod(x, y):
    s = 1
    while y:
        if y & 1:
            s *= x
        x *= x
        y >>= 1
    return s

def dfs(i, mul, calc):
    global Ans
    if calc >= Ans:
        return
    if i > p[0]:
        if mul >= X:
            Ans = mn(Ans, calc)
        return
    for cnt in range(0, num[i] + 1, 2):
        if cnt == 0:
            dfs(i + 1, mul, calc)
            continue
        if cmp(mul, p[i], cnt):
            Ans = mn(Ans, calc + dp[i][cnt])
            return
        dfs(i + 1, mul * quick_mod(p[i], cnt), calc + dp[i][cnt])

p[0] = 0
for i in range(1, n + 1):
    who = 0
    for j in range(1, p[0] + 1):
        if p[j] == s[i - 1][0]:
            who = j
    if who == 0:
        p[0] += 1
        p[p[0]] = s[i - 1][0]
        dp[p[0]][1] = s[i - 1][1]
        num[p[0]] = 1
    else:
        num[who] += 1
        for j in range(num[who], 0, -1):
            dp[who][j] = mn(dp[who][j], dp[who][j - 1] + s[i - 1][1])

dfs(1, 1, 0)
if Ans == float('inf'):
    print("-1")
else:
    print(Ans)
