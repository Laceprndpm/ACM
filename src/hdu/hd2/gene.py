import random

def generate_test_case(max_n, max_R):
    n = random.randint(1, max_n)
    R = random.randint(1, max_R)
    a = [random.randint(1, R) for _ in range(n)]
    return n, R, a

def generate_test_data(T, max_n, max_R, output_file):
    with open(output_file, 'w') as f:
        f.write(f"{T}\n")
        for _ in range(T):
            n, R, a = generate_test_case(max_n, max_R)
            f.write(f"{n} {R}\n")
            f.write(" ".join(map(str, a)))
            f.write("\n")

if __name__ == "__main__":
    # 参数配置
    T = 1                  # 测试数据组数
    max_n = 5000            # 最大n值
    max_R = 10**9           # 最大R值
    output_file = "P1007.data"  # 输出文件名
    
    # 生成数据
    generate_test_data(T, max_n, max_R, output_file)
    print(f"已生成测试数据并保存到 {output_file}")
