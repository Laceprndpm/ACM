/*
5
2 5
b10 101
10 + 101 = 110 = 10 ^ 101
怎么样才能不一样呢...

6 6
b110 110
19 10
1010000
 101100

10100
 1010

11000
01111
100000
011111
10100
 1011
只要存在两个位都为1，就一定不行吗？没错
但是如果直接加那一位，则会出现错误
1024 4096
1198372 599188
*/
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 x, y;
    cin >> x >> y;
    if (x == y) {
        cout << "-1\n";
        return;
    }
    // i64 ans = 0;
    // i64 c   = 0;
    int meet11 = -1;
    i64 ans    = 0;
    for (int i = 0; i <= 62; i++) {
        if ((x >> i & 1) && (y >> i & 1)) {
            meet11 = i;
            break;
        }
        if ((x >> i & 1) != (y >> i & 1)) {
            break;
        }
    }
    if (meet11 != -1) {
        for (int i = meet11; i <= 62; i++) {
            if (i == meet11 || ((x >> i & 1) == 0 && (y >> i & 1) == 0)) {
                ans |= 1 << i;
            }
            if ((x >> i & 1) != (y >> i & 1)) {
                break;
            }
        }
    }
    x += ans;
    y += ans;
    for (int i = 0; i <= 40; i++) {
        if (((x >> i & 1) ^ (y >> i & 1)) && (x >> (i + 1) & 1) == (y >> (i + 1) & 1)) {
            ans |= (1ll << i);
            x += 1ll << i;
            y += 1ll << i;
        }
    }
    cout << ans << '\n';
    // do {
    //     c          = 0;
    //     i64 curans = 0;
    //     i64 owe    = 0;
    //     for (int i = 62; i >= 0; i--) {
    //         i64 curx = x >> i & 1;
    //         i64 cury = y >> i & 1;
    //         if (curx & cury) {
    //             owe = 1;
    //             c   = 1;
    //         } else if (curx | cury) {
    //             if (owe) {
    //                 owe = 0;
    //                 curans |= (1 << i);
    //             }
    //         }
    //         if (owe && !curx && !cury) {
    //             curans |= (1 << i);
    //         }
    //     }
    //     x += curans;
    //     y += curans;
    //     ans |= curans;
    // } while (c);
    // 101
    // 001
    // 011
    // 11101
    // 10011
    // 11001
    //    01
    //   110
    //   100
    //    01
    // 100100100100100110000
    //  10010010010010100000
    // 0b100100100100100100100
    //  0b10010010010010010100
    // 000000000000000000001
    // 0b100100100100100101000
    //  0b10010010010010011000
    // 00000000000000000001
    // 0b100100100100100110000
    //  0b10010010010010100000
    // 0000000000000000001
    // 0b100100100100101000000
    //  0b10010010010010110000
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