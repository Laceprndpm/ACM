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
    int    n;
    string s;
    cin >> n;
    cin >> s;
    vector<int> preifx1(n + 1);
    vector<int> suffix2(n + 1);
    for (int i = 0; i < n; i++) {
        preifx1[i + 1] = (s[i] == '1' ? 1 + preifx1[i] : 0);
    }
    for (int i = n - 1; i >= 0; i--) {
        suffix2[i] = (s[i] == '2' ? 1 + suffix2[i + 1] : 0);
    }
    int ans = 1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '/') ans = max(min(preifx1[i], suffix2[i + 1]) * 2 + 1, ans);
    }
    cout << ans << '\n';
    return 0;
}