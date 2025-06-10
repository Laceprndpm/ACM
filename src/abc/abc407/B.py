X, Y = list(map(int, input().split()))
A = B = [i for i in range(1, 7, 1)]
cnt = 0
for i in A:
    for j in B:
        if (i + j >= X) or (abs(i - j) >= Y):
            cnt += 1
print(cnt / 36)
