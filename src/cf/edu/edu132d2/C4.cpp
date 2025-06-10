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
    int cnt  = 0;
    int cnt2 = 0;
    for (char i : s) {
        if (i == '(') {
            cnt++;
        } else if (i == ')') {
            cnt--;
        } else {
            cnt2++;
        }
    }
    // if (abs(cnt) == cnt2) {
    //     cout << "Yes\n";
    //     return;
    // }

    int need1 = (cnt2 - cnt) / 2;
    int need2 = (cnt2 + cnt) / 2;
    if (need1 == 0 || need2 == 0) {
        cout << "Yes\n";
        return;
    }
    int l = 0, r = s.length() - 1;
    while (l < s.length() && need1) {
        if (s[l] == '?') {
            s[l] = '(';
            need1--;
        }
        l++;
    }
    while (r >= 0 && need2) {
        if (s[r] == '?') {
            s[r] = ')';
            need2--;
        }
        r--;
    }
    s[l - 1]  = ')';
    s[r + 1]  = '(';
    bool flag = false;
    cnt = 0;
    for (char i : s) {
        if (i == '(') {
            cnt++;
        } else if (i == ')') {
            cnt--;
        }
        if (cnt < 0) {
            flag = true;
            break;
        }
    }
    if (!flag) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
    }
}

// (*(())
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