n, m, k, x = map(int, input().split())
print((x + pow(10, k, n) * m % n) % n)
