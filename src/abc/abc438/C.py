n = int(input())
ai = list(map(int, input().split()))
lft = [i - 1 for i in range(n)]
rgt = [i + 1 for i in range(n)]
lft[0] = 0
checklist = [i for i in range(n)]
die = [False] * n
while checklist:
    cur = checklist.pop()
    tmp = []
    flag = True
    for _ in range(4):
        if cur == n:
            flag = False
            break
        if die[cur]:
            flag = False
            break
        tmp.append(cur)
        cur = rgt[cur]
    if not flag:
        continue
    for i in tmp:
        if ai[i] != ai[tmp[0]]:
            flag = False
            break
    if not flag:
        continue
    for i in tmp:
        die[i] = True
    rgt[lft[tmp[0]]] = rgt[tmp[-1]]
    if rgt[tmp[-1]] != n:
        lft[rgt[tmp[-1]]] = lft[tmp[0]]
    cur = lft[tmp[0]]
    for _ in range(3):
        if cur == -1:
            break
        if die[cur]:
            break
        checklist.append(cur)
        cur = lft[cur]
ans = 0
for i in range(n):
    if not die[i]:
        ans += 1
print(ans)