# 把输出输出到output

with open("output", "w") as f:
    ans = 1
    for i in range(1, int(1e9 + 1)):
        ans = ans * i % (10**9 + 7)
        if i % 1000000 == 0:
            f.write(f"{ans},")