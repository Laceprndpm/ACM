N = int(1e7)
phi = [0] * (N + 1)
is_prime = [True] * (N + 1)
primes = []
phi[1] = 1
for i in range(2, N + 1):
    if is_prime[i]:
        primes.append(i)
        phi[i] = i - 1
    for p in primes:
        if i * p > N:
            break
        is_prime[i * p] = False
        if i % p == 0:
            phi[i * p] = phi[i] * p
            break
        else:
            phi[i * p] = phi[i] * (p - 1)


T = int(input())


def solve(p):
    if p == 1:
        return 0
    return pow(2, solve(phi[p]) % phi[p] + phi[p], p)


for _ in range(T):
    n = int(input())
    print(solve(n))
