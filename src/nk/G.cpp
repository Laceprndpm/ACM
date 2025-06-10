#include <math.h>

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n;
    cin >> n;
    vector<i64> arr(n + 5);
    int         blocks = ceil(sqrtl(n));
    int         cnt    = 0;
    for (int i = 1; i <= blocks; i++) {
        for (int j = blocks * blocks - blocks + i; j > 0; j -= blocks) {
            if (j <= n) arr[++cnt] = j;
        }
    }
    // for (int i = blocks * blocks, j = n; i > blocks * blocks - blocks; i--, j--) {
    //     arr[j] = arr[i];
    // }
    // for (int i = blocks * blocks - blocks + 1, j = n; j > blocks * blocks; i++, j--) {
    //     arr[i] = j;
    // }
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << ' ';
    }
    cout << '\n';
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