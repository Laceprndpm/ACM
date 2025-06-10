#include <iostream>
#include <utility>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

string S = "9876543210";

void solve()
{
    string s;
    cin >> s;
    for (int i = 0; i < 10; i++) {
        for (int j = i; j < 10; j++) {
            if (s[j] >= S[i] && s[j] < s[i]) {
                swap(s[j], s[i]);
            }
        }
    }
    cout << s << '\n';
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