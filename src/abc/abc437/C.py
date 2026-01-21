def solve():
    n = int(input())
    arr = []
    power = 0
    for i in range(n):
        a, b = map(int, input().split())
        arr.append((a, b))
        power += b
    arr = sorted(arr, key=lambda x: x[0] + x[1])
    for i in range(n):
        power -= arr[i][0] + arr[i][1]
        if power < 0:
            print(i)
            return
    print(n)


T = int(input())
for _ in range(T):
    solve()
