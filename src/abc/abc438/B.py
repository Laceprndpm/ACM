n, m = map(int, input().split())
s = input()
t = input()
ans = int(1e9)
for i in range(n - m + 1):
    cnt = 0
    for j in range(m):
        tmp = int(s[i + j]) - int(t[j])
        if tmp < 0:
            tmp += 10
        cnt += tmp
    ans = min(ans, cnt)
print(ans)