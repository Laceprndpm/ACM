import math


# def f(x):
#     l = []
#     for i in range(1, math.isqrt(x) + 1):
#         if x % i == 0:
#             l.append(i)
#             if i != x // i:
#                 l.append(x // i)
#     return l

# a = f(981700934653)
# a.sort()
# for i in a:
#     print(i) 

n = int(input())
lst = {}
sum = 0
for i in range(math.isqrt(n), 1, -1):
    if n % i == 0:
        lst[i] = 1
        sum += 1
        while n % i == 0:
            n //= i
            lst[i] += 1
            sum += 1
if n > 1:
    lst[n] = 1
num = 0
for i in range(math.isqrt(n), 0, -1):
    if n % i == 0:
        num += 1
        if i != n // i:
            num += 1

if num % 2 == 1:
    print("N")
else:
    if sum >= num:
        print("Y")
    else:
        print("N")