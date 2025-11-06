n, l, r = map(int, input().split())
if l + r > 2 and l + r <= n + 1:
    l = l - 1
    r = r - 1
    cur = n - 1
    lft = []
    rgt = []
    mid = []
    for i in range(l):
        lft.append(cur)
        cur -= 1
    lft.reverse()
    for i in range(r):
        rgt.append(cur)
        cur -= 1
    while cur >= 1:
        mid.append(cur)
        cur -= 1
    if l != 0:
        ans = lft + mid + [n] + rgt
    else:
        ans = lft + [n] + mid + rgt
    print("yes")
    print(" ".join(map(str, ans)))
else:
    print("no")
