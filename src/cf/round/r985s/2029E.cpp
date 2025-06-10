#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

// vectors
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

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
} prime(4e5);

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // different prime has different sons
    // 对不同p进行dp，时间复杂度大概是多少呢？
    // 可以3e4 * 4e5
    // tle吗？
    // 如果分治
    // 对不同n进行暴力，时间复杂度大概是多少呢？
    // 可以
    // 秒了？
    // 如果先对2进行dp，随后每次只dp到2 * p
    // 不太行吧？
    // 2 4 6 8 9 10 12 14 15 16 18 20 21 22 24...
    // 2难道可以产生所有合数？
    // m = p * q, p < q
    // 假如出现了 2 * p, 则可以一直加p知道遇到q
    // p * 2  , p * 3
    //
    //
    //
    // cout << sz(prime.primes);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int& i : arr) {
            cin >> i;
        }
        vector<int> ps;
        for (int i = 0; i < n; i++) {
            if (prime.minp[arr[i]] == arr[i]) {
                ps.push_back(i);
            }
        }
        if (sz(ps) == 0) {
            cout << "2\n";
            continue;
        }
        if (sz(ps) >= 2) {
            cout << "-1\n";
            continue;
        }
        if (sz(ps) == 1) {
            int  p_idx = ps[0];
            int  p     = arr[p_idx];
            bool ok    = 1;
            for (int i : arr) {
                if (i == p) continue;
                if (i < 2 * p) {
                    cout << "-1\n";
                    ok = 0;
                    break;
                }
                if (i % 2 && i - prime.minp[i] < 2 * p) {
                    cout << -1 << '\n';
                    ok = 0;
                    break;
                }
            }
            if (ok) cout << p << '\n';
        }
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */