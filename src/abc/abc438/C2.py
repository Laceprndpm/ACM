n = int(input())
ai = list(map(int, input().split()))
res = []
for x in ai:
    res.append(x)
    if len(res) >= 4 and all(res[-i] == x for i in range(1, 5)):
        for _ in range(4):
            res.pop()
print(len(res))
