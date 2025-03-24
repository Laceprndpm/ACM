#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;
int         m;
int         k;
vector<int> arr;

class PrimeSieve {
public:
    PrimeSieve(int n) : n(n), is_prime(n + 1, true)
    {
        sieve();
    }

    bool isPrime(int x)
    {
        return is_prime[x];
    }

private:
    int          n;
    vector<bool> is_prime;

    void sieve()
    {
        is_prime[0] = is_prime[1] = false;
        for (int i = 2; i * i <= n; ++i) {
            if (is_prime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    is_prime[j] = false;
                }
            }
        }
    }
} prime((int)5e7);

int dfs(int idx, int sum, int remain)
{
    if (remain == 0) {
        if (prime.isPrime(sum)) {
            return 1;
        }
    }
    if (idx >= m) {
        return 0;
    }
    if (m - idx < remain) {
        return 0;
    }

    return dfs(idx + 1, sum + arr[idx], remain - 1) + dfs(idx + 1, sum, remain);
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> m;
    cin >> k;
    arr.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> arr[i];
    }
    cout << dfs(0, 0, k);
    return 0;
}