#include <iostream>
#include <vector>
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
    int n, c;
    cin >> n >> c;
    vector<int> input(n);
    int         last = -1;
    int         cur;
    int         cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> cur;
        if (last == -1 || cur - last >= c) {
            cnt++;
            last = cur;
        }
    }
    cout << cnt << '\n';
    return 0;
}