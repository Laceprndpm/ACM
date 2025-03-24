#define REMOVE_ME
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
    int t;
    cin >> t;
    int maxE   = 0;
    int minE   = 100;
    i64 totoal = 0;
    for (int i = 1; i <= t; i++) {
        int cur;
        cin >> cur;
        totoal += cur;
        maxE = max(cur, maxE);
        minE = min(cur, minE);
    }
    cout << maxE << '\n';
    cout << minE << '\n';
    printf("%.2lf", (double)totoal / t);
    return 0;
}