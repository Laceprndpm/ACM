import random
N = int(1e5)
K = int(1e5)
print(N, K)
hirange = int(1e4)
# 用硬件随机数生成器初始化随机数种子
random.seed()
A = [random.randint(1, hirange + 1) for _ in range(N)] # 随机数
for i in A:
    print(i, end=" ")
print()
