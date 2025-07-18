#include <cstddef>
#include <cstring>
#include <iostream>
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

constexpr i64 MOD = 19260817;

struct Node {
    bool sp           = 0;
    i64  status[3][3] = {0};
};

const Node L  = {1, {{1, 0, 0}, {0, 1, 0}, {0, 0, 0}}};
const Node LL = {0, {{1, 1, 0}, {1, 0, 0}, {0, 0, 1}}};

Node operator+(const Node& l, const Node& r)
{
    if (l.sp && r.sp) {
        return LL;
    }
    if (l.sp) {
        Node x;
        // A:
        auto& c = x.status;
        for (int i = 1; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                c[i][j] += r.status[i - 1][j];
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                x.status[0][j] += r.status[i][j];
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                x.status[i][j] %= MOD;
            }
        }
        return x;
    }
    if (r.sp) {
        Node x;
        // A:
        auto& c = x.status;
        for (int i = 0; i < 3; i++) {
            for (int j = 1; j < 3; j++) {
                c[i][j] += l.status[i][j - 1];
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                c[i][0] += l.status[i][j];
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                c[i][j] %= MOD;
            }
        }
        return x;
    }
    Node  x;
    auto &a = l.status, &b = r.status;
    auto& c = x.status;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                for (int kk = 0; kk + k <= 2; kk++) {
                    c[i][j] += a[i][k] * b[kk][j];
                }
            }
            c[i][j] %= MOD;
        }
    }
    // 0|0
    // BBB
    // BAB
    //
    // 0|1
    // BBA
    // 0|2
    // BAA
    // 1|0
    // ABB
    // 1|1
    // ABA
    // 2|0
    // AAB
    //
    return x;
}

void solve()
{
    // 假设我有l和r的答案
    // l中
    // l中以AA,A结尾的答案有多少？r中以A,AA开头的答案有多少？
    // x  bb                        b 0
    // a l[a][bb] * (r[0][bb]) + l[a][b] * r[0]
    // aa
    // 0
    //
    i64 n;
    cin >> n;
    Node base = L;
    Node ans;
    bool iszero = true;
    while (n) {
        if (n & 1) {
            if (iszero) {
                ans    = base;
                iszero = 0;
            } else
                ans = ans + base;
        }
        base = base + base;
        n >>= 1;
    }
    i64 ansval = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ansval += ans.status[i][j];
        }
    }
    ansval %= MOD;
    cout << ansval << '\n';
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
    i64 m;
    cin >> m;
    while (m--) {
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