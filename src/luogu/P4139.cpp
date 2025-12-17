#include <bits/stdc++.h>
using namespace std;

static const int N = 10000000;

int         phi[N + 1];
bool        is_prime[N + 1];
vector<int> primes;

int solve(int p)
{
    if (p == 1) return 0;
    int t = solve(phi[p]);
    // powmod(2, t % phi[p] + phi[p], p)
    long long e    = (t % phi[p] + phi[p]) % phi[p] + phi[p];  // 原样照搬你的写法
    long long base = 2 % p;
    long long res  = 1;
    long long mod  = p;
    while (e) {
        if (e & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        e >>= 1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 线性筛
    fill(is_prime, is_prime + N + 1, true);
    is_prime[0] = is_prime[1] = false;
    phi[1]                    = 1;
    for (int i = 2; i <= N; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int p : primes) {
            long long v = 1LL * i * p;
            if (v > N) break;
            is_prime[v] = false;
            if (i % p == 0) {
                phi[v] = phi[i] * p;
                break;
            } else {
                phi[v] = phi[i] * (p - 1);
            }
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        cout << solve(n) << "\n";
    }

    return 0;
}
