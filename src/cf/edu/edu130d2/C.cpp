#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int i = 0, j = 0;
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    bool flag   = true;
    int  extraA = 0;
    int  needC  = 0;
    for (int i = 0; i < n; i++) {
        if ((s[i] == 'a' || t[i] == 'a') && needC) {
            flag = false;
            break;
        }
        if ((s[i] == 'c' || t[i] == 'c') && extraA) {
            flag = false;
            break;
        }
        if (t[i] == s[i]) {
            continue;
        } else if (t[i] == 'a') {
            if (s[i] == 'b') {
                if (extraA) {
                    extraA--;
                    continue;
                } else {
                    flag = false;
                    break;
                }
            } else if (s[i] == 'c') {
                flag = false;
                break;
            }
        } else if (t[i] == 'b') {
            if (s[i] == 'a') {
                extraA++;
                continue;
            } else if (s[i] == 'c') {
                if (needC) {
                    needC--;
                } else {
                    flag = false;
                    break;
                }
            }
        } else if (t[i] == 'c') {
            if (s[i] == 'a') {
                flag = false;
                break;
            } else if (s[i] == 'b') {
                needC++;
            }
        }
    }
    if (extraA || needC) {
        flag = false;
    }
    if (flag) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
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