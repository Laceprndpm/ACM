import sys

sys.set_int_max_str_digits(12000)

# with open("/home/patchouli/Code/ACM/src/luogu/P2613_1.in", "r") as f:
a = int(input())
b = int(input())

# def moudle(x):
#     res = 0
#     for ch in x:
#         res = (res * 10 + int(ch)) % 19260817
#     return res

# a = moudle(a)
# b = moudle(b)
a = a % 19260817
b = b % 19260817


def exgcd(a: int, b: int):
    if b == 0:
        return (1, 0, a)
    la, lb, r = exgcd(b, a % b)
    x = lb
    y = la - lb * (a // b)
    return x, y, r


x, y, r = exgcd(b, 19260817)
if a % r != 0:
    print("Angry!")
else:
    k = a // r
    mod_result = 19260817 // r  # M'

    x_initial = x * k

    x = (x_initial % mod_result + mod_result) % mod_result

    print(x)
