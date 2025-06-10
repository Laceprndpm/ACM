#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct Prime {
    vector<int> minp, primes;

    Prime(int n)
    {
        sieve(n);
    }

    void sieve(int n)
    {
        minp.assign(n + 1, 0);
        primes.clear();

        for (int i = 2; i <= n; i++) {
            if (minp[i] == 0) {
                minp[i] = i;
                primes.push_back(i);
            }

            for (auto p : primes) {
                if (i * p > n) {
                    break;
                }
                minp[i * p] = p;
                if (p == minp[i]) {
                    break;
                }
            }
        }
    }
} p(1e7);

vector<i64> prefix((i64)4e5 + 5);

void solve()
{
    // 全部互质，那么只能全部都是质数吧
    // 如果有不是质数的出现，那么必然存在比他小的质数没出现过
    int n;
    cin >> n;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    priority_queue<i64, vector<i64>, greater<>> pq;
    i64                                         sumArr = 0;
    for (int i = 0; i < n; i++) {
        pq.push(arr[i]);
        sumArr += arr[i];
    }
    int i = n;
    while (prefix[i] > sumArr) {
        i--;
        sumArr -= pq.top();
        pq.pop();
    }
    cout << n - i << '\n';
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
    for (int i = 0; i <= (i64)4e5; i++) {
        prefix[i + 1] = prefix[i] + p.primes[i];
    }
    while (t--) {
        solve();
    }
    return 0;
}