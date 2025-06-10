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
    int n;
    cin >> n;
    i64 sum = 0;
    for (int i = 0; i < n - 1; i++) {
        int cur;
        cin >> cur;
        sum += cur;
    }
    cout << -sum << '\n';
    return 0;
}