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
    int cnt    = 0;
    int status = 0;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (s == "login") {
            status = 1;
        }
        if (s == "logout") {
            status = 0;
        }
        if (s == "private" && status != 1) {
            cnt++;
        }
    }
    cout << cnt << '\n';
    return 0;
}