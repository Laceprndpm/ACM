import random

MAXN = int(2e5)


def gen_random_ints(N, K):
    cuts = sorted(random.sample(range(K + N - 1), N - 1))
    cuts = [-1] + cuts + [K + N - 1]
    return [cuts[i + 1] - cuts[i] - 1 for i in range(N)]


random.seed()
for testcase in range(5):
    with open(f"./data/random{testcase}.in", "w") as f:
        T = int(1e4)
        f.write(f"{T}\n")
        cases = gen_random_ints(T, int(MAXN))
        for case in cases:
            f.write(f"{case}\n")
            for i in range(case):
                f.write(f"{random.randint(1, case)} ")
            f.write("\n")
for testcase in range(5, 10):
    with open(f"./data/random{testcase}.in", "w") as f:
        T = int(1e2)
        f.write(f"{T}\n")
        cases = gen_random_ints(T, int(MAXN))
        for case in cases:
            f.write(f"{case}\n")
            for i in range(case):
                f.write(f"{random.randint(1, max(case // 10 ** (testcase - 5), 1))} ")
            f.write("\n")

for testcase in range(10, 15):
    with open(f"./data/random{testcase}.in", "w") as f:
        T = int(1)
        f.write(f"{T}\n")
        cases = gen_random_ints(T, int(MAXN))
        for case in cases:
            f.write(f"{case}\n")
            for i in range(case):
                f.write(f"{random.randint(1, max(case // 10 ** (testcase - 10), 1))} ")
            f.write("\n")

for testcase in range(15, 16):
    with open(f"./data/random{testcase}.in", "w") as f:
        T = int(1)
        f.write(f"{T}\n")
        f.write(f"{MAXN}\n")
        for i in range(MAXN):
            f.write("1 ")
        f.write("\n")

for testcase in range(16, 17):
    with open(f"./data/random{testcase}.in", "w") as f:
        T = int(1)
        f.write(f"{T}\n")
        f.write(f"{198765}\n")
        for i in range(1, 631):
            for j in range(631 - i):
                f.write(f"{i} ")
        f.write("\n")
    # >>> (630 + 1) * 630 / 2
    # =198765
for testcase in range(17, 18):
    with open(f"./data/random{testcase}.in", "w") as f:
        T = int(1)
        f.write(f"{T}\n")
        f.write(f"{MAXN}\n")
        for i in range(MAXN // 2):
            f.write("1 ")
        for i in range(2, MAXN // 2 + 2):
            f.write(f"{i} ")
        f.write("\n")
