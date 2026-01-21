import sys

output = []


def solve():
    n, k = map(int, input().split())
    arr = list(map(int, sys.stdin.readline().split()))
    dp = [int(-1e9)] * (k + 1) * (k + 1)
    dp[k * (k + 1)] = 0
    maxn = 0
    need_add = 0
    for i in range(n):
        if arr[i] <= maxn:
            need_add += 1
            continue
        maxn = arr[i]
        if need_add > 0:
            for j in range(k + 1):
                for u in range(k - j + 1):
                    dp[j * (k + 1) + u] += need_add * u
        need_add = 0
        tmp_dp = [-int(1e9)] * (k + 1)
        for j in range(k + 1):
            for u in range(k - j + 1):
                tmp_dp[j] = max(tmp_dp[j], dp[j * (k + 1) + u])
        for j in range(k + 1):
            for u in range(min(j, arr[i]) + 1):
                dp[(j - u) * (k + 1) + u] = max(dp[(j - u) * (k + 1) + u], tmp_dp[j])
        for j in range(k + 1):
            for u in range(k - j + 1):
                dp[j * (k + 1) + u] += u
    if need_add > 0:
        for j in range(k + 1):
            for u in range(k - j + 1):
                dp[j * (k + 1) + u] += need_add * u
    output.append(str(max(dp)))


t = int(input())
for _ in range(t):
    solve()
sys.stdout.write("\n".join(output))
