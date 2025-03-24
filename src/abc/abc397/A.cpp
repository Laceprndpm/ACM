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
    double t;
    cin >> t;

    if (t >= 38.0) {
        cout << 1 << '\n';
    } else if (t >= 37.5) {
        cout << 2 << '\n';
    } else {
        cout << 3 << '\n';
    }
    
    return 0;
}