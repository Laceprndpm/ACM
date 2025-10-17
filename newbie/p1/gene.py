import random

N = int(1e5)  # 字符串长度的一半


def gen_random_ints(N, K):
    cuts = sorted(random.sample(range(K + N - 1), N - 1))
    cuts = [-1] + cuts + [K + N - 1]
    return [cuts[i + 1] - cuts[i] - 1 for i in range(N)]


def gen_random_positive_ints(N, K):
    if K < N:
        raise ValueError("K must be >= N")
    # 生成 N 个非负整数和为 K - N
    points = sorted(random.sample(range(1, K), N - 1))
    points = [0] + points + [K]
    return [points[i + 1] - points[i] for i in range(N)]


random.seed()
for testcase in range(5):
    with open(f"./data/random{testcase}.in", "w") as f:
        T = int(1e4)
        f.write(f"{T}\n")
        cases = gen_random_positive_ints(T, int(N))
        for case in cases:
            output = "(" * case + ")" * case
            case *= 2
            # 打乱字符串
            output = list(output)
            random.shuffle(output)
            output = "".join(output)
            f.write(f"{case}\n")
            f.write(f"{output}\n")
for testcase in range(5, 10):
    with open(f"./data/random{testcase}.in", "w") as f:
        T = int(1e1)
        f.write(f"{T}\n")
        cases = gen_random_positive_ints(T, int(N))
        for case in cases:
            output = "(" * case + ")" * case
            case *= 2
            # 打乱字符串
            output = list(output)
            random.shuffle(output)
            output = "".join(output)
            f.write(f"{case}\n")
            f.write(f"{output}\n")
testcase = 10
with open(f"./data/random{testcase}.in", "w") as f:
    T = 1
    f.write(f"{T}\n")
    case = N
    output = "(" * case + ")" * case
    case *= 2
    # 打乱字符串
    output = list(output)
    random.shuffle(output)
    output = "".join(output)
    f.write(f"{case}\n")
    f.write(f"{output}\n")
testcase = 11
with open(f"./data/random{testcase}.in", "w") as f:
    T = 1
    f.write(f"{T}\n")
    case = N
    output = ")" * case + "(" * case
    case *= 2
    f.write(f"{case}\n")
    f.write(f"{output}\n")