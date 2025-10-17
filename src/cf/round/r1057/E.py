import sys

input = lambda: sys.stdin.readline().strip()

M = 10**7
pr = [1] * (M + 1)

for i in range(2, M + 1):
    if pr[i] == 1:
        for j in range(i, M + 1, i):
            pr[j] = i

t = int(input())
outs = []

fmin = lambda x, y: x if x < y else y

inf = 10**9

for _ in range(t):
    n, m = map(int, input().split())

    vis = set()

    for i in range(n, 0, -1):
        x = i
        while x > 1:
            vis.add(pr[x])
            x //= pr[x]

        if pr[i] == i:
            break

    ans = 0

    def f(val, p):
        c = 0
        while val:
            val //= p
            c += val
        return c

    for i in range(n - 1, 0, -1):
        res = inf

        for v in vis:
            cur = v
            c = 1

            v1 = f(i, v)
            v2 = f(n, v)

            while cur <= m:

                if v1 // c != v2 // c:
                    res = fmin(res, v1 // c)

                cur *= v
                c += 1

        ans += res

        if pr[i] == i:
            break

    outs.append(ans)

print("\n".join(map(str, outs)))
