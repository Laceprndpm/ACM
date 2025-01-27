# %%
def exgcd(a : int, b : int):
    if (b == 0):
        return (1, 0, a)
    la, lb, r = exgcd(b, a % b)
    x = lb
    y = la - lb * (a // b)
    return x, y, r

# %%
def linear_equation(a, b, c): # non_limit
    if (a == 0 and b == 0):
            if (c != 0):
                 return (False,)
            else:
                 return True, False, (None, None)
    if (a == 0):
         if (c % b == 0):
              return True, False, (None, c // b)
         else:
              return (False,)
    if (b == 0):
         if (c % a == 0):
              return True, False, (c // a, None)
         else:
              return (False,)
         
    x, y, r = exgcd(a, b)
    if (c % r != 0):
        return (False,)
    else:
        k = (c // r)
        x = x * k; y = y * k
        return True, True, (x, y), (b // r, a // r)

# %%
import math
def solve(a1, b1, c1, a2, b2, c2): # a1, b1 != 0 and a2, b2 != 0
    # a1 x + b1 x = c1
    # a2 x**2 + b2 y**2 = c2
    A = int(a2 * b1 ** 2 + a1**2 * b2)
    B = int(-2 * a2 * b1 * c1)
    C = int(a2 * c1 ** 2 - a1 ** 2 * c2)
    delta = int(round(math.sqrt(B ** 2 - 4 * A * C)))
    if (delta ** 2 != B ** 2 - 4 * A * C):
        print("NO")
        return
    if ((-B + delta) % (2 * A) == 0):
        result_1 = (-B + delta) // (2 * A)
        if ((c1 - b1 * result_1) % a1 == 0):
            x = int((c1 - b1 * result_1) / a1)
            print("YES")
            print(x, result_1)
            return
    if ((-B - delta) % (2 * A) == 0):
        result_2 = (-B + delta) // (2 * A)
        if ((c1 - b1 * result_2) % a1 == 0):
            x = int((c1 - b1 * result_2) / a1)
            print("YES")
            print(x, result_2)
            return
    print("NO")
    return


# %%


# %%
def main_func(a1, b1, c1, a2, b2, c2):
        result_1 = linear_equation(a1, b1, c1)

        if (a2 == 0 and b2 == 0):
            if (c2 == 0):
                if (result_1[0]):
                    print(*[i if i is not None else 0 for i in result_1[2]])
                else:
                    print("NO")
            else:
                print("NO")
            return

        if (a2 == 0):
            y = int(math.sqrt(c2 / b2))
            if (y ** 2 * b2 == c2):
                x = int((c1 - y * b1) / a1)
                if (x * a1 + y * b1 == c1):
                    print("YES")
                    print(x, y)
                else:
                    print("NO")
            else:
                print("NO")
            return

        if (b2 == 0):
            x = int(math.sqrt(c2 / a2))
            if (x ** 2 * b2 == c2):
                y = int((c1 - x * b1) / a1)
                if (x * a1 + y * b1 == c1):
                    print("YES")
                    print(x, y)
                else:
                    print("NO")
            else:
                print("NO")
            return
        
        if (result_1[1]):
            solve(a1, b1, c1, a2, b2, c2)
            return
        
        if (result_1[0]):
            x, y = result_1[2]
            if (x is None):
                x = int(math.sqrt(c2 - b2 * y ** 2))
                if (a2 * x ** 2 + b2 * y ** 2 == c2):
                    print("YES")
                    print(x, y)
                else:
                    print("NO")
            else:
                y = int(math.sqrt(c2 - a1 * x ** 2))
                if (a2 * x ** 2 + b2 * y ** 2 == c2):
                    print("YES")
                    print(x, y)
                else:
                    print("NO")
            return
        print("FO")

# %%
if __name__ == "__main__":
    T = int(input()) # 输入T
    for _ in range (T):
        
        a1, b1, c1, a2, b2, c2 = map(int, input().split()) # 接收a, b, c
        main_func(a1, b1, c1, a2, b2, c2)



