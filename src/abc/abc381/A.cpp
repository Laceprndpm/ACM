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
    string s;
    cin >> s;
    if (n % 2 == 0) {
        cout << "No\n";
        return 0;
    }
    int i;
    for (i = 0; i < (n + 1) / 2 - 1; i++) {
        if (s[i] != '1') {
            cout << "No\n";
            return 0;
        }
    }
    if (s[i] != '/') {
        cout << "No\n";
        return 0;
    }
    for (i++; i < n; i++) {
        if (s[i] != '2') {
            cout << "No\n";
            return 0;
        }
    }
    cout << "Yes\n";
    return 0;
}