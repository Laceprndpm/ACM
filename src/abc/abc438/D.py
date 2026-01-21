n = int(input())
arr = list(map(int, input().split()))
brr = list(map(int, input().split()))
crr = list(map(int, input().split()))
dpa = 0
dpb = -int(1e9)
dpc = -int(1e9)
for i in range(n):
    if i != 1:
        dpc = max(dpc + crr[i], dpb + crr[i])
    if i != 0:
        dpb = max(dpb + brr[i], dpa + brr[i])
    dpa += arr[i]
print(dpc)
