H, W = list(map(int, input().split()))
ans = 0
bd = [[0 for _ in range(W)] for _ in range(H)]
vis = [[0 for _ in range(W)] for _ in range(H)]
temp = 0
for i in range(H):
    bd[i] = list(map(int, input().split()))
for i in bd:
    for j in i:
        temp ^= j


def dfs(cur, val):
    global ans
    curX = cur // W
    curY = cur % W
    if cur == H * W:
        ans = max(ans, val)
        return
    if vis[curX][curY] == 1:
        dfs(cur + 1, val ^ bd[curX][curY])
    else:
        if curY + 1 < W and vis[curX][curY + 1] == 0:
            vis[curX][curY] = vis[curX][curY + 1] = 1
            dfs(cur + 1, val ^ bd[curX][curY])
            vis[curX][curY] = vis[curX][curY + 1] = 0
        if curX + 1 < H and vis[curX + 1][curY] == 0:
            vis[curX][curY] = vis[curX + 1][curY] = 1
            dfs(cur + 1, val ^ bd[curX][curY])
            vis[curX][curY] = vis[curX + 1][curY] = 0
        dfs(cur + 1, val)


dfs(0, temp)
print(ans)
