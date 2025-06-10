#include <algorithm>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    string sc = s;
    reverse(sc.begin(), sc.end());
    if (s < sc) {
        cout << "Yes\n";
        return;
    }
    if (unique(s.begin(), s.end()) - s.begin() != 1) {
        if (k != 0) {
            cout << "Yes\n";
            return;
        }
    }
    cout << "No\n";
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