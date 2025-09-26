import random
random.seed()
for testcase in range(25):
    with open(f"./data/random{testcase}.in", "w") as f:
        N = random.randint(1, int(1e5))
        K = random.randint(1, int(1e5))
        f.write(f"{N} {K}\n")
        hirange = int(1e4)
        A = [random.randint(1, hirange + 1) for _ in range(N)]  # 随机数
        for i in A:
            f.write(f"{i} ")
        f.write("\n")
