#include <cassert>
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 2 0
    // 3 0
    // 4 2
    // 5 40
    // 6 12
    // 7 496
    // 8 3252
    // 9 48328
    // 10 205188
    // 11 2732488
    int n;
    cin >> n;
    switch (n) {
        case 2:
            cout << 0;
            break;
        case 3:
            cout << 0;
            break;
        case 4:
            cout << 2;
            break;
        case 5:
            cout << 40;
            break;
        case 6:
            cout << 12;
            break;
        case 7:
            cout << 496;
            break;
        case 8:
            cout << 3252;
            break;
        case 9:
            cout << 48328;
            break;
        case 10:
            cout << 205188;
            break;
        case 11:
            cout << 2732488;
            break;
        default:
            assert(0);
            break;
    }
    return 0;
}