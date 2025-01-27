import math
a = [0, 0, 0]
b = [0, 0, 0]
c = [0, 0, 0]
x0, y0 = 0, 0
lim = 1000000

def exgcd(a, b):
    global x0
    global y0
    if b == 0:
        x0 = 1; y0 = 0; return a
    gcd = exgcd(b, a % b)
    x0, y0 = y0, x0 - a // b * y0
    return gcd

def check(x, y): # x, y回代是否可以满足
    if x < -lim or x > lim or y < -lim or y > lim or x != int(x) or y != int(y):
        return False
    if a[1] * x + b[1] * y != c[1]:
        return False
    return a[2] * (x ** 2) + b[2] * (y ** 2) == c[2]

def Try(y):
    x = round((c[1] - b[1] * y) / a[1])
    if check(x, y):
        print("Yes\n%d %d" % (x, y)); return True
    return False

T = int(input()) # 输入T
for _ in range(T):
    a[1], b[1], c[1], a[2], b[2], c[2] = map(int, input().split()) # 接收a, b, c
    if a[1] == 0 and b[1] == 0: # 如果a1和b1均为0
        print("No"); continue
    
    if a[1] == 0: # 如果仅a1为0
        y = c[1] // b[1] # 求出y
        if a[2] == 0: # 如果a2也为0
            x = 0 # x置0
        else:
            if (c[2] - b[2] * (y ** 2)) / a[2] < 0: # x**2 <= 0
                print("No"); continue
            x = int(math.sqrt((c[2] - b[2] * (y ** 2)) / a[2]))
        if check(x, y): # 是否合理
            print("Yes\n%d %d" % (x, y)); continue
        else:
            print("No"); continue
        
    if b[1] == 0: # 如果a1!=0，但b1为0，由对称性，和前面一样
        x = c[1] // a[1]
        if b[2] == 0:
            y = 0
        else:
            if (c[2] - a[2] * (x ** 2)) / b[2] < 0:
                print("No"); continue
            y = int(math.sqrt((c[2] - a[2] * (x ** 2)) / b[2]))
        if check(x, y):
            print("Yes\n%d %d" % (x, y)); continue
        else:
            print("No"); continue
        
    gcd = exgcd(a[1], b[1]) # a1，b1无0
    # x0 * a[1] + y0 * b[1] == gcd
    if c[1] % gcd: # exgcd求丢番图方程
        print("No"); continue
    a[1] //= gcd; b[1] //= gcd; c[1] //= gcd
    # x0 * a[1] + y0 * b[1] == 1
    x0 *= c[1]; y0 *= c[1]
    # x0 * a[1] + y0 * b[1] == c[1]
    k = b[1]; l = a[1]


    if a[2] == 0 and b[2] == 0 and c[2] != 0:
        print("No"); continue # 0 != c
    elif a[2] == 0 and b[2] == 0 and c[2] == 0: # 归一化x, y
        
        l1, r1 = (-lim - x0) / k, (lim - x0) / k # x的index的左右边界
        l2, r2 = (-lim - y0) / (-l), (lim - y0) / (-l) # y的index的左右边界
        l1, r1 = min(l1, r1), max(l1, r1)
        l2, r2 = min(l2, r2), max(l2, r2)
        left, right = math.ceil(max(l1, l2)), math.floor(min(r1, r2)) # 交集
        t = (left + right) // 2
        x, y = x0 + k * t, y0 - l * t

        if check(x, y):
            print("Yes\n%d %d" % (x, y)); continue
        print("No"); continue
    else:
        # 推测消x
        # a1 * x + b1 * y = c1
        # a2 * x ** 2 + b2 * y ** 2 = c2
        # a1 * x = c1 - b1 * y
        # a2 * x ** 2 = a2 * (c1 ** 2 - 2 * b1 * y *c1 + b1 ** 2 * y **2) / a1 ** 2
        A = (a[2] * b[1] * b[1]) / (a[1] * a[1]) + b[2]
        B = -(2 * a[2] * c[1] * b[1]) / (a[1] * a[1])
        C = (a[2] * c[1] * c[1]) / (a[1] * a[1]) - c[2]
        Delta = round(B * B - 4 * A * C, 4)
        if A == 0:
            if B == 0:
                y1 = y2 = 0
            else:
                y1 = y2 = round((-C) / B)
        else:
            if Delta < 0:
                print("No", Delta); continue
            BA = (-B) / (2 * A)
            y1 = round(BA - math.sqrt(Delta / (4 * A * A)))
            y2 = round(BA + math.sqrt(Delta / (4 * A * A)))
        flag = True
        for d in range(-5, 5):
            if flag:
                y = y1 + d
                if Try(y):
                    flag = False; break
                y = y2 + d
                if Try(y):
                    flag = False; break
        if flag:
            print("No")
