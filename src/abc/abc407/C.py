s = input()
ans = 0
for i in range(len(s)):
    if i == 0:
        ans += 1
        continue
    else:
        ans += (int(s[i - 1]) - int(s[i])) % 10 + 1
ans += int(s[len(s) - 1])
print(ans)
