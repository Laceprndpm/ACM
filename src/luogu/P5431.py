n, p, k = map(int, input().split())
arr = list(map(int, input().split()))
ans = 0
for i in range(n):
    ans += pow(k, i + 1, p) * pow(arr[i], -1, p) % p
    ans %= p
print(ans % p)
