#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

bool check(int x)
{
    while (x) {
        if (x % 10 == 2) {
            return true;
        }
        x /= 10;
    }
    return false;
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
    int ans = 0;
    for (int i = 1; i <= 2020; i++) {
        if (check(i)) {
            ans++;
        }
    }
    cout << ans << '\n';
    return 0;
}