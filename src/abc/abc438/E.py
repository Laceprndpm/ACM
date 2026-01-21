import sys

input = sys.stdin.readline
n, q = map(int, input().split())
arr = list(map(int, input().split()))
for i in range(n):
    arr[i] -= 1
querys = []
for _ in range(q):
    querys.append(tuple(map(int, input().split())))
binary_arr = [[arr, [i + 1 for i in range(n)]]]
for _ in range(30):
    prev_arr, prev_cost = binary_arr[-1]
    new_arr = [0] * n
    new_cost = [0] * n
    for i in range(n):
        new_arr[i] = prev_arr[prev_arr[i]]
        new_cost[i] = prev_cost[i] + prev_cost[prev_arr[i]]
    binary_arr.append([new_arr, new_cost])
for query in querys:
    k, x = query
    x -= 1
    ans = 0
    for i in range(31):
        if (k >> i) & 1:
            arr_i, cost_i = binary_arr[i]
            ans += cost_i[x]
            x = arr_i[x]
    print(ans)
