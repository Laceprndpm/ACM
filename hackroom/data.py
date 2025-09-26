with open("input.in", "w") as f:
    T = 1
    N = int(2e5)
    f.write(f"{T}\n")
    f.write(f"{N}\n")
    for i in range(N):
        if(i % 2 == 0):
            f.write('a')
        else:
            f.write('b')
    f.write('\n')