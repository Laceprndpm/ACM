N = int(input()) + 2
S = "#" + input() + "#"
R = [0] + list(map(int, input().split())) + [0]

now = "#"
mx = 0
cnt = 0
rle = []

for i in range(N):
    if S[i] == now:
        if mx == R[i]:
            cnt += 1
        elif mx < R[i]:
            mx = R[i]
            cnt = 1
    else:
        rle.append((mx, cnt))
        now = S[i]
        mx = R[i]
        cnt = 1

rle = rle[1:]
mx = max(rle)[0]
ans = 0

for i in range(0, len(rle) - 1, 2):
    if max(rle[i][0], rle[i + 1][0], rle[i + 2][0]) == mx:
        ans += rle[i][1] * rle[i + 2][1]

print(ans)

# 7
# .#.#.#.
# 1 1000 500 1000 500 1000 1
