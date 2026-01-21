n, k = map(int, input().split())
st = set()
for i in range(2**n):
    s = bin(i)[2:].zfill(n)
    flag = True
    for j in range(0, n - k):
        tmp = s[j : j + k]  # 从第 j 位开始取 k 位
        if tmp.count(tmp[0]) <= k // 2:
            flag = False
            break
    if flag:
        st.add(s[: n - k + 1])
arr = list(st)
arr.sort()

for s in arr:
    print(s)

print(len(arr))