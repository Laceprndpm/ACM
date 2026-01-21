import bisect

n, m = map(int, input().split())
arr = list(map(int, input().split()))
brr = list(map(int, input().split()))
arr.sort()
brr.sort()
res = 0
for ai in arr:
    pos = bisect.bisect_left(brr, ai)
    res += pos * ai - (m - pos) * ai
    res %= 998244353
for bi in brr:
    pos = bisect.bisect_right(arr, bi)
    res += (pos) * bi - (n - pos) * bi
    res %= 998244353
print(res)
