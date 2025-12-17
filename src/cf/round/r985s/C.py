def main():
    n = int(input())
    arr = list(map(int, input().split()))
    dp = [0] + [-1e9] * 2
    for i in range(n):
        ndp = dp.copy()
        cur = arr[i]
        for j in [0, 2]:
            if cur < ndp[j]:
                ndp[j] -= 1
            elif cur > ndp[j]:
                ndp[j] += 1
            else:
                pass
        ndp[1] = max(dp[0], ndp[1])
        ndp[2] = max(ndp[1], ndp[2])
        dp = ndp
    print(dp[2])


T = int(input())
for _ in range(T):
    main()
