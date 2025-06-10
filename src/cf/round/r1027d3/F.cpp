#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
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
} prime(1e6);

vector<int> candidate;
int         k;

int solveone(int x)
{
    candidate.clear();
    for (int i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            candidate.push_back(i);
            candidate.push_back(x / i);
        }
    }
    sort(all(candidate));
    map<int, int>      cost;
    function<int(int)> dfs = [&](int x) {
        if (x == 1) return 0;
        if (cost.count(x) != 0) return cost[x];
        int cur_cost = INF;
        for (int i = 1; i < sz(candidate); i++) {
            if (candidate[i] > k) break;
            if (x % candidate[i] != 0) continue;
            cur_cost = min(cur_cost, 1 + dfs(x / candidate[i]));
        }
        return cost[x] = cur_cost;
    };
    return dfs(x);
}

void solve()
{
    int x, y;
    cin >> x >> y >> k;
    int tx = x, ty = y;
    int gc = gcd(x, y);
    tx /= gc, ty /= gc;
    int ans1 = solveone(tx), ans2 = solveone(ty);
    int ans = -1;
    if (ans1 + ans2 < INF) {
        ans = ans1 + ans2;
    }
    cout << ans << '\n';
    // auto dx = [](int tx) {
    //     map<int, int> px;
    //     for (int i : prime.primes) {
    //         while (tx % i == 0) {
    //             px[i]++;
    //             tx /= i;
    //         }
    //         if (tx == 1 || i * i > tx) {
    //             break;
    //         }
    //     }
    //     return px;
    // };
    // map<int, int> px = dx(x), py = dx(y);
    // set<int>      need_i;
    // for (auto i : px) {
    //     need_i.insert(i.first);
    // }
    // for (auto i : py) {
    //     need_i.insert(i.first);
    // }
    // map<int, int> need;
    // for (int i : need_i) {
    //     need[i] = py[i] - px[i];
    // }
    // map<map<int, int>, int> op;
    // auto                    bfs1 = [&](auto cur) {
    //     i64 res = 1;
    //     for (auto i : cur) {

    //     }
    // };
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
    // x = p1^a1 * p2^a2 * p3^a3
    // y = p1^b1 * p2^b2 * p3^b3
    // to minimum the op times of turn x into y
    // maybe dfs?because its really hard to choose which p to increase and increase how many
    // how imple
    // decrease X must later than increase it, and only once
    // Does d(x) everytime very expensive?no, cause already know p
    // here we go
    // fuck I mistake the meaning
    //
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