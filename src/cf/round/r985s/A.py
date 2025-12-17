output = []

def main():
    l, r, k = map(int, input().split())
    realr = r // k
    output.append(max(realr - l + 1, 0))


T = int(input())
for i in range(T):
    main()

print("\n".join(map(str, output)))