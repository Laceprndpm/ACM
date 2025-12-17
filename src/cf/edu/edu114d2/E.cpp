#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>
using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

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
#define mt      make_tuple
#define fi      first
#define se      second

constexpr int P = 998244353;

constexpr u64 power(u64 a, u64 b)
{
    u64 res = 1;
    for (; b != 0; b /= 2, a = a * a % P) {
        if (b & 1) {
            res = (res * a) % P;
        }
    }
    return res;
}

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    map<pair<int, int>, int> points;

    int cadj = 0, radj = 0;

    int                   row[2][2]{}, col[2][2]{};
    int                   slide[2][2]{};
    vector<array<int, 2>> rowadj(n + 1), coladj(m + 1);
    vector<int>           rowcnt(n + 1), colcnt(m + 1);
    int                   rowc = 0, colc = 0;
    auto                  remove = [&](pair<int, int> x) {
        if (points.count(x)) {
            int val = points[x];
            points.erase(points.find(x));
            slide[val][(x.fi + x.se) % 2]--;

            if (--rowadj[x.fi][(x.se + val) % 2] == 0 && rowadj[x.fi][!((x.se + val) % 2)]) {
                radj--;
            }
            if (--coladj[x.se][(x.fi + val) % 2] == 0 && coladj[x.se][!((x.fi + val) % 2)]) {
                cadj--;
            }
            if (--rowcnt[x.fi] == 0) {
                rowc--;
            }
            if (--colcnt[x.se] == 0) {
                colc--;
            }
        }
    };
    auto add = [&](pair<int, int> x, int val) {
        points[x] = val;
        slide[val][(x.fi + x.se) % 2]++;
        if (++rowadj[x.fi][(x.se + val) % 2] == 1 && rowadj[x.fi][!((x.se + val) % 2)]) {
            radj++;
        }
        if (++coladj[x.se][(x.fi + val) % 2] == 1 && coladj[x.se][!((x.fi + val) % 2)]) {
            cadj++;
        }
        if (++rowcnt[x.fi] == 1) {
            rowc++;
        }
        if (++colcnt[x.se] == 1) {
            colc++;
        }
    };
    for (int i = 0; i < k; i++) {
        int x, y, val;
        cin >> x >> y >> val;
        remove({x, y});
        if (val != -1) add({x, y}, val);
        if (cadj && radj) {
            cout << 0 << '\n';
            continue;
        }
        i64 ans = 0;
        if (!radj) {
            ans += power(2, n - rowc);
        }
        if (!cadj) {
            ans += power(2, m - colc);
        }
        if (slide[0][0] * slide[0][1] == 0 && slide[1][0] * slide[1][1] == 0 && slide[0][0] * slide[1][0] == 0
            && slide[0][1] * slide[1][1] == 0) {
            ans--;
        }
        if (rowc == 0 && colc == 0) {
            ans--;
        }
        ans += P;
        ans %= P;
        cout << ans << '\n';
    }
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
    int t = 1;
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