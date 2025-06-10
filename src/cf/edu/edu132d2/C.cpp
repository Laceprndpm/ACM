#include <algorithm>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    string s;
    cin >> s;
    int cnt = 0;
    for (auto iter = s.begin() + 1; iter != s.begin() + s.length() - 1; iter++) {
        if (*iter == '(') {
            cnt++;
        }
        if (*iter == ')') {
            cnt--;
        }
        if (*iter == '?') {
            cnt++;
        }
    }
    if (cnt == 0) {
        cout << "Yes\n";
        return;
    }
    cnt = 0;
    for (auto iter = s.begin() + 1; iter != s.begin() + s.length() - 1; iter++) {
        if (*iter == '(') {
            cnt++;
        }
        if (*iter == ')') {
            cnt--;
        }
        if (*iter == '?') {
            cnt--;
        }
    }
    if (cnt == 0) {
        cout << "Yes\n";
        return;
    }
    cout << "No\n";
    // int notsure = 0;
    // int sureL   = 0;
    // int sureR   = 0;

    // if (cnt == 0 && notsure == 0) {
    //     cout << "Yes\n";
    //     return;
    // }
    // if (abs(cnt) == notsure) {
    //     cout << "Yes\n";
    //     return;
    // }
    // cout << "No\n";
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