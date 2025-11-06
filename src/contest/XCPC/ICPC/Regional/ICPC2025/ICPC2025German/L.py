t = int(input())
if t > 600:
    print(max(t - 600, 45))
elif t > 585:
    print(45)
elif t > 570:
    print(t - 540)
elif t > 390:
    print(30)
elif t > 360:
    print(t - 360)
else:
    print(0)
