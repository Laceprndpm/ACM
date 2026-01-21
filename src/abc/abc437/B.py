h, w, n = map(int, input().split())
st = {}
for i in range(h):
    row = list(map(int, input().split()))
    for j in range(w):
        st[row[j]] = i
st2 = {}
for _ in range(n):
    a = int(input())
    if a not in st:
        continue
    if st[a] in st2:
        st2[st[a]] += 1
    else:
        st2[st[a]] = 1
if not st2:
    print(0)
else:
    print(max(st2.values()))
