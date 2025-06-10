#include <cassert>
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
// u64           a = 0, b = 0, c = 0;
u64  cur[3] = {0, 0, 0};
int  cnt    = 0;
bool is0    = false;
u64  n;
int  qt = 0;

u64 query(u64 l, u64 r)
{
    qt++;
    assert(qt <= 150);
    cout << "xor " << l << ' ' << r << endl;
    u64 res;
    cin >> res;
    return res;
}

void binary_query(u64 l, u64 r, u64 range_ans)
{
    if (cnt > 2) return;
    if (range_ans == 0) {
        return;
    }
    if (l >= r) {
        cur[cnt++] = range_ans;
        return;
    }
    if (cnt == 2 && is0) {
        cur[2] = cur[0] ^ cur[1];
        cnt++;
        return;
    }
    u64 mid  = (r - l) / 2ull + l;
    u64 lres = query(l, mid);
    if (lres == range_ans) {
        binary_query(l, mid, lres);
        return;
    } else if (lres == 0ull) {
        binary_query(mid + 1ull, r, range_ans ^ lres);
        return;
    } else if (lres != 0 && lres != range_ans) {
        binary_query(l, mid, lres);
        binary_query(mid + 1ull, r, range_ans ^ lres);
        return;
    }
}

void solve()
{
    qt  = 0;
    cnt = 0;
    cin >> n;
    u64 tmp = query(1ull, n);
    if (tmp == 0) {
        is0   = 1;
        int i = 1;
        u64 res;
        for (; i < 64; i++) {
            u64 guess = (1ull << i) - 1ull;
            res       = query(1ull, guess);
            if (res != 0ull) {
                cur[cnt++] = res;
                break;
            }
        }
        binary_query(1ull << i, n, res);
    } else {
        is0 = 0;
        binary_query(1ull, n, tmp);
    }
    cout << "ans ";
    for (int i = 0; i < 3; i++) {
        cout << cur[i] << ' ';
    }
    cout << endl;
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
    //  10
    //  11
    // 101
    // if a + b = c
    // a ^ b = c
    // a < b
    // a ^ b ^ c = 0
    // 假如C的最高位是k
    // 那么1 << k - 1一定 >= a
    // 所以只要按位枚举 -63
    // 然后就可以找到a的范围，然后二分一下64
    // 不，可以直接找到A了
    // 随后二分可以找到bc吗？
    // 可以吧？不断二分，把为0的区域给丢弃
    //
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