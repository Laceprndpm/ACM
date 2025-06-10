#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

class PrimeSieve {
public:
    PrimeSieve(int n) : n(n), is_prime(n + 1, true)
    {
        sieve();
    }

    bool query(int num) const
    {
        if (num <= n) {
            return is_prime[num];
        }
        return false;
    }

private:
    int               n;
    std::vector<bool> is_prime;

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
} prime(1e7 + 50);

void solve()
{
    int n;
    cin >> n;
    i64 ans = 0;
    for (int i = 2; i <= n; i++) {
        if (prime.query(i)) {
            i64 maxA = n / i;
            ans += maxA;
        }
    }
    cout << ans << '\n';
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}