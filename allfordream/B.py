t = int(input())

for _ in range(t):
    n = int(input())
    board = []
    for i in range(n):
        row = input()
        board.append(row)
    i_min_j = {}
    i_add_j = {}
    sharpcnt = 0
    ok = 0
    for i in range(n):
        for j in range(n):
            if board[i][j] == "#":
                i_min_j[i - j] = 1
                i_add_j[i + j] = 1
                sharpcnt += 1
    for i in range(n - 1):
        for j in range(n - 1):
            cur = 0
            for dx, dy in [(0, 0), (0, 1), (1, 0), (1, 1)]:
                if board[i + dx][j + dy] == "#":
                    cur += 1
            if cur == sharpcnt:
                ok = 1
    for st in [i_min_j, i_add_j]:
        if len(st) <= 2:
            for i in st:
                if i + 1 in st:
                    ok = 1
        if len(st) <= 1:
            ok = 1
    if ok:
        print("YES")
    else:
        print("NO")
