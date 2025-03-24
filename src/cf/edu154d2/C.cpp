#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    string input;
    cin >> input;
    stack<int> status;
    int        cnt = 0;
    // 0 模糊，1，排序，-1未排序
    for (char i : input) {
        if (i == '+') {
            if (cnt == 0) {
                status.push(1);
                cnt = 1;
                continue;
            } else {
                if (status.top() == 1) {
                    status.push(0);
                } else if (status.top() == 0) {
                    status.push(0);
                } else if (status.top() == -1) {
                    status.push(-1);
                }
                cnt++;
            }
        }
        if (i == '-') {
            if (cnt == 1) {
                status.pop();
                cnt = 0;
            } else {
                if (status.top() == 1) {
                    status.pop();
                    if (status.top() == -1) {
                        cout << "NO\n";
                        return;
                    }
                    status.top() = 1;
                } else if (status.top() == 0) {
                    status.pop();
                } else if (status.top() == -1) {
                    status.pop();
                }
                cnt--;
            }
        }
        if (i == '1') {
            if (cnt > 1 && status.top() == -1) {
                cout << "NO\n";
                return;
            }
            if (!status.empty())
                status.top() = 1;
        }
        if (i == '0') {
            if (cnt <= 1 || status.top() == 1) {
                cout << "NO\n";
                return;
            }
            status.top() = -1;
        }
    }
    cout << "YES\n";
}

signed main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}