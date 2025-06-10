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
    int n, q;
    cin >> n >> q;
    int          num = n;
    vector<bool> arr(n + 1, true);
    while (q--) {
        int t;
        cin >> t;
        if (arr[t]) {
            arr[t] = false;
            num--;
        } else {
            arr[t] = true;
            num++;
        }
    }
    cout << num << '\n';
    return 0;
}