def main():
    n = int(input())
    s1 = input()
    s2 = input()
    cnt0 = s1.count('0')
    cnt1 = s1.count('1')
    for i in s2:
        if cnt0 == 0 or cnt1 == 0:
            print("No")
            return
        if i == '0':
            cnt1 -= 1
        else:
            cnt0 -= 1
    print("Yes")

T = int(input())
for i in range(T):
    main()