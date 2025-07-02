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
    vector<int>         minp, primes;
    vector<vector<int>> rd;

    Prime(int n)
    {
        sieve(n);
    }

    auto getRes()
    {
        return rd;
    }

    void sieve(int n)
    {
        minp.assign(n + 1, 0);
        primes.clear();
        rd.resize(n + 1);
        for (int i = 2; i <= n; i++) {
            if (minp[i] == 0) {
                minp[i] = i;
                primes.push_back(i);
                rd[i].push_back(i);
            }

            for (auto p : primes) {
                if (i * p > n) {
                    break;
                }
                minp[i * p] = p;
                rd[minp[i]].push_back(i * p);
                if (p == minp[i]) {
                    break;
                }
            }
        }
    }
};

void solve()
{
    int n;
    cin >> n;
    Prime       p(n);
    vector<int> ans(n + 1);
    auto        res = p.getRes();
    for (auto r : res) {
        for (int i = 0; i < r.size(); i++) {
            ans[r[i]] = r[(i + 1) % r.size()];
        }
    }
    ans[1] = 1;
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 假如p为质数，如果2p在n内，则轮换，否则他只能 = p
    // 之后我们就筛掉了大部分质数吧
    // 或者也可以线性筛改一下
    int t;
    cin >> t;
    while (t--) {
        solve();
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