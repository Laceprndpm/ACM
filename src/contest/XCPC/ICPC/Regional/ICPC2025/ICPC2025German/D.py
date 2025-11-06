n = int(input())
points = []
mxX = -(10**9)
mnX = 10**9
mxY = -(10**9)
mnY = 10**9
for i in range(n):
    x, y = map(int, input().split())
    points.append((x, y))
    mxX = max(mxX, x)
    mnX = min(mnX, x)
    mxY = max(mxY, y)
    mnY = min(mnY, y)
print(4)
print(mxX, mxY)
print(mnX, mxY)
print(mnX, mnY)
print(mxX, mnY)
