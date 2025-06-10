#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

int S(int x)
{
    i64 ans = 0;
    while (x) {
        ans += x % 10;
        x /= 10;
    }
    return ans;
}

void solve()
{
    int n;
    cin >> n;
    int _;
    cout << "mul 9" << endl;
    cin >> _;
    for (int i = 0; i < 2; i++) {
        cout << "digit" << endl;
        cin >> _;
    }
    cout << "add " << n - 9 << endl;
    cin >> _;
    cout << "!" << endl;
    cin >> _;
}

// void dbg(int x, int n)
// {
//     // x *= 3;
//     for (int i = 0; i < 3; i++) {
//         x = S(x);
//     }
//     for (int i = 0; i < 3; i++) {
//         if (x - 3 > 0) {
//             x -= 3;
//         }
//     }
//     x += n - 3;
//     cout << x << '\n';
// }

signed main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    // // int n, x;
    // // cin >> n >> x;
    // // dbg(n, x);
    while (t--) {
        solve();
    }

    return 0;
}