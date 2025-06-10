def solve():
    n = int(input())
    a = list(map(int, input().split()))
    a = [0] + a
    l = [n] * (n + 1)  # l[x] = 最左出现位置
    r = [0] * (n + 1)  # r[x] = 最右出现位置

    for i in range(1, n + 1, 1):
        l[a[i]] = min(l[a[i]], i)
        r[a[i]] = max(r[a[i]], i)

    L, R = n, 0
    f = [0] * (n + 1)  # 差分数组，最终统计满足条件的起点数量

    for i in range(1, n + 1, 1):
        L = min(L, l[i])
        R = max(R, r[i])
        if (R - L + 1) <= i:
            left = max(1, R - i + 1)
            right = min(n, L + i - 1)
            f[left] += 1
            if right < n:
                f[right + 1] -= 1
        else:
            break
    for i in range(1, n + 1):
        f[i] += f[i - 1]

    ans = f.count(n)
    print(ans)


t = int(input())
for _ in range(t):
    solve()
